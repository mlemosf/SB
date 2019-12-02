#include "../include/Heap.hpp"

Heap* Heap::_heap = NULL;

Heap::Heap(){}

Heap::~Heap(){
    free(this->_heap);
}

Heap* Heap::getInstance(){
    if (!_heap)
        _heap = new Heap();
    
    return _heap;
}

void Heap::setPath(std::string path){
    this->path = path + "/";
}

std::string Heap::getPath() const {
    return path;
}

void Heap::runMain(Leitor *mainClass){
    JavaClassInstance* mainInstance = new JavaClassInstance();
    mainInstance->javaClass = mainClass;


    /* will search for a public method in the entrypoint class: "public void main(String[])"
    see: https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-5.html#jvms-5.2
    */
    u2 index;
    bool found_main_index = false;
    std::string method_name, method_descriptor;
    for(index = 0; index < mainClass->get(METHODS_COUNT); index++){
        method_name = mainClass->getUTF8(mainClass->getMethods()->methods[index]->name_index);
        method_descriptor = mainClass->getUTF8(mainClass->getMethods()->methods[index]->descriptor_index);
        
        if(
            method_name.compare("main") == 0 &&
            method_descriptor.compare("([Ljava/lang/String;)V") == 0
            //@@ && mainClass->isMethodAccessFlagSet(index, ACC_PUBLIC)
        ){
            found_main_index = true;
            break;
        }
    }

    // if the index containing the method is not found then the program exits
    if(!found_main_index){
        std::cout << "(E) Could not find the entrypoint method of " /*<< @@ mainClass->classFilePath*/ << ". Terminating execution..." << std::endl;
        return;
    }

    // Caso exista um método "main", adiciona a classe ao unordered_map de instâncias.
    std::string key(mainClass->getUTF8(mainClass->getConstantPool()->getCpInfoElement(mainClass->get(THIS_CLASS)-1).constant_element.c1->name_index));
    key += ".class";
    _instantiatedClasses[key] = mainInstance;
    
    // Carrega os Fields associados à classe.
    // addStaticFields(mainInstance);

    Frame *frame = new Frame(mainClass, mainClass->getConstantPool(), index, mainInstance);
    _executionFrames.push(frame);
    // _executionFrames.top()->executeFrame();


    while(!_executionFrames.empty()){
        _executionFrames.top()->executeFrame();
    }
}

void Heap::pushFrame(Frame* frame){
    _executionFrames.push(frame);
}

void Heap::popFrame(){
    _executionFrames.pop();
}

Leitor* Heap::getClass(std::string className){
    std::string basePath = getPath();
    std::string key = basePath + className + ".class";
    // std::cout << "getClass: " << key << std::endl;

    Leitor *javaClass = _loadedClasses[key];
    if(javaClass == nullptr){
        javaClass = new Leitor();
        //@@ javaClass->readClassFile(key);
        loadClass(javaClass);
    }

    return javaClass;
}

void Heap::loadClass(Leitor *jc){
    std::string thisClass = jc->getUTF8(jc->getConstantPool()->getCpInfoElement(jc->get(THIS_CLASS)-1).constant_element.c1->name_index);
    thisClass += ".class";

    // std::cout << "loadClass: " << thisClass << std::endl;
    _loadedClasses[thisClass] = jc;

    JavaClassInstance *staticInstance;
    staticInstance = new JavaClassInstance();
    staticInstance->javaClass = jc;
    addStaticFields(staticInstance);
    _instantiatedClasses[thisClass] = staticInstance;
}

void Heap::addStaticFields(JavaClassInstance* _classInstance){
    _classInstance->fieldVariables = new std::unordered_map<std::string, Variable*>();
    Leitor *javaClass = _classInstance->javaClass;
    std::string superClass, thisClass;
    u2 *superClassRef = &javaClass->getConstantPool()->getCpInfoElement(javaClass->get(SUPER_CLASS)-1).constant_element.c1->name_index;
    u2 *thisClassRef  = &javaClass->getConstantPool()->getCpInfoElement(javaClass->get(THIS_CLASS)-1).constant_element.c1->name_index;

    do{
        superClass = javaClass->getUTF8(*superClassRef);
        thisClass  = javaClass->getUTF8(*thisClassRef);
        for(u2 i = 0; i < javaClass->get(FIELDS_COUNT); i++){
            // Apenas Fields com a flag "static";
            if(javaClass->getFields()[i].getAcessFlags() & 0x8){
                // std::cout << "Lendo o Field " << i+1 << " da classe " << thisClass << std::endl;
                int name_index = javaClass->getFields()[i].getNameIndex();
                int type_index = javaClass->getFields()[i].getDescriptorIndex();
                std::string name(javaClass->getUTF8(name_index));
                std::string desc(javaClass->getUTF8(type_index));
                (*_classInstance->fieldVariables)[name] = new Variable(desc);
            }
        }
        if(superClass.compare("java/lang/Object") != 0){
            javaClass = Heap::getInstance()->getClass(superClass);
            break;
        }
    } while(superClass.compare("java/lang/Object") != 0);
}

void Heap::addInstanceFields(JavaClassInstance* _classInstance){
    _classInstance->fieldVariables = new std::unordered_map<std::string, Variable*>();
    Leitor *javaClass = _classInstance->javaClass;
    std::string superClass, thisClass;
    u2 *superClassRef = &javaClass->getConstantPool()->getCpInfoElement(javaClass->get(SUPER_CLASS)-1).constant_element.c1->name_index;
    u2 *thisClassRef  = &javaClass->getConstantPool()->getCpInfoElement(javaClass->get(THIS_CLASS)-1).constant_element.c1->name_index;

    do{
        superClass = javaClass->getUTF8(*superClassRef);
        thisClass  = javaClass->getUTF8(*thisClassRef);
        for(u2 i = 0; i < javaClass->get(FIELDS_COUNT); i++){
            int name_index = javaClass->getFields()[i].getNameIndex();
            int type_index = javaClass->getFields()[i].getDescriptorIndex();
            std::string name(javaClass->getUTF8(name_index));
            std::string desc(javaClass->getUTF8(type_index));
            (*_classInstance->fieldVariables)[javaClass->getUTF8(name_index)] = new Variable(desc);
        }
        if(superClass.compare("java/lang/Object") != 0){
            javaClass = Heap::getInstance()->getClass(superClass);
            break;
        }
    } while(superClass.compare("java/lang/Object") != 0);
}

Frame* Heap::frameTop() {
    return _executionFrames.top();
}

JavaClassInstance* Heap::getInstantiatedClass(std::string cn) {
    std::size_t i = cn.rfind("/");
    std::string classPath(&cn[i + 1]);
    classPath += ".class";

    return _instantiatedClasses[classPath];
}

Variable* Heap::getStaticInfo(std::string cn, std::string fn) {
    std::string s(fn);
    std::size_t i = cn.rfind("/");
    std::string classPath(&cn[i + 1]);
    classPath += ".class";

    JavaClassInstance *javaClassInstance = _instantiatedClasses[classPath];

    return (*javaClassInstance->fieldVariables)[s];
}