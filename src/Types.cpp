#include "include/Types.hpp"
#include "include/Heap.hpp"

Variable::Variable(std::string descriptor, void* init_val){
    std::string aux(descriptor);

    if((aux.compare("B") == 0) || (aux.compare("C") == 0) || (aux.compare("D") == 0) ||
        (aux.compare("F") == 0) || (aux.compare("I") == 0) || (aux.compare("J") == 0) ||
        (aux.compare("S") == 0) || (aux.compare("Z") == 0))
    {
        int type = (int)aux[0] - 65;

        // Aloca o espaço da variável e a inicia
        this->variable = (PrimitiveTypes*)malloc(sizeof(PrimitiveTypes));
        switch(type){
            case 1:     // B - Signed byte
                tag = _byte;
                variable->byteValue = (uint32_t*)malloc(sizeof(uint32_t));
                *variable->byteValue = (init_val != nullptr) ? *((u1*)init_val) : 0;
                break;
            case 2:     // C - Unicode character
                tag = _char;
                variable->charValue = (uint32_t*)malloc(sizeof(uint32_t));
                *variable->charValue = (init_val != nullptr) ? *((u1*)init_val) : 0;
                break;
            case 3:     // D - Double-precision floating-point
                tag = _double;
                variable->doubleValue = (uint64_t*)malloc(sizeof(uint64_t));
                *variable->doubleValue = (init_val != nullptr) ? *((u8*)init_val) : 0;
                break;
            case 5:     // F - Single-precision floating-point
                tag = _float;
                variable->floatValue = (uint32_t*)malloc(sizeof(uint32_t));
                *variable->floatValue = (init_val != nullptr) ? *((u4*)init_val) : 0;
                break;
            case 8:     // I - Integer
                tag = _int;
                variable->intValue = (uint32_t*)malloc(sizeof(uint32_t));
                *variable->intValue = (init_val != nullptr) ? *((u4*)init_val) : 0;
                break;
            case 9:     // J - Long
                tag = _long;
                variable->longValue = (uint64_t*)malloc(sizeof(uint64_t));
                *variable->longValue = (init_val != nullptr) ? *((u8*)init_val) : 0;
                break;
            case 18:    // S - Signed short
                tag = _short;
                variable->shortValue = (uint32_t*)malloc(sizeof(uint32_t));
                *variable->shortValue = 0;
                break;
            case 25:    // Z - True or False
                tag = _bool;
                variable->booleanValue = (uint32_t*)malloc(sizeof(uint32_t));
                *variable->booleanValue = 0;
                break;
        }
    }
    else if(aux[0] == '['){
        tag = _array;
        array = (arrayVariable*)malloc(sizeof(arrayVariable));
        array->array = new std::vector<Variable*>();
    }
    else if(aux.compare("Ljava/lang/String;") == 0) {
        tag = _string;
        string = (init_val != nullptr) ? (std::string*)init_val : new std::string();
    }
    else if(aux[0] == 'L'){
        tag = _classInstance;
        std::string name = "";
        for(unsigned int i = 1; i < aux.length()-1; i++)
            name += aux.at(i);
        this->object = (JavaClassInstance*)malloc(sizeof(JavaClassInstance));
        this->object->javaClass = Heap::getInstance()->getClass(name);
    }
    else if(aux.compare("RA") == 0){
		tag = _returnAddress;
		returnAddress = (uint32_t*)malloc(sizeof(uint32_t));
		returnAddress = 0;
    }
}

Variable::Variable(){
    tag = _void;
}

Variable* copyVariable(Variable *_var) {
	Variable *var = NULL;

    if(_var->tag == Variable::_void){
        var = new Variable();
    }
	else if(_var->tag == Variable::_byte){
        var = new Variable("B");
        *var->variable->byteValue = *_var->variable->byteValue;
    } else if (_var->tag == Variable::_bool){
        var = new Variable("Z");
        *var->variable->booleanValue = *_var->variable->booleanValue;
    } else if (_var->tag == Variable::_char){
        var = new Variable("C");
        *var->variable->charValue = *_var->variable->charValue;
    } else if (_var->tag == Variable::_short){
        var = new Variable("S");
        *var->variable->shortValue = *_var->variable->shortValue;
    } else if (_var->tag == Variable::_int){
        var = new Variable("I");
        *var->variable->intValue = *_var->variable->intValue;
    } else if (_var->tag == Variable::_float){
        var = new Variable("F");
        *var->variable->floatValue = *_var->variable->floatValue;
    } else if (_var->tag == Variable::_long){
        var = new Variable("J");
        *var->variable->longValue = *_var->variable->longValue;
    } else if (_var->tag == Variable::_double){
        var = new Variable("D");
        *var->variable->doubleValue = *_var->variable->doubleValue;
    } else if (_var->tag == Variable::_classInstance){
        std::string aux = "L";
        
        cp_info *cp = &var->object->javaClass->constant_pool[var->object->javaClass->this_class - 1];
        aux += var->object->javaClass->getUtf8(cp->info.classInfo.name_index);

        var = new Variable(aux);
    } else if (_var->tag == Variable::_array){
        var = new Variable("[");
        for(unsigned i = 0; i < _var->array->array->size(); i++){
            Variable *aux = copyVariable(_var->array->array->at(i));
            var->array->array->push_back(aux);
        }
    } else if (_var->tag == Variable::_string){
        var = new Variable("Ljava/lang/String;");
        *var->string = *_var->string;
    } else if (_var->tag == Variable::_returnAddress){
        var = new Variable("RA");
        *var->returnAddress = *_var->returnAddress;
    }

	return var;
}