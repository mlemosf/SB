// #include "Constants.hpp"
// #include "Structs.hpp"
// #include "JavaClass.hpp"
#include "Frame.hpp"
#include "leitor.hpp"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <cstring>

/** \class Heap
 *  \brief Classe que estabelece a área de dados da Java Virtual Machine.
 * 
 *  A classe Heap é responsável por definir as estruturas e métodos necessários para
 *  a alocação dos dados de todas as classes Java envolvidas em uma execução da
 *  Java Virtual Machine.
 */
class Heap {
    public:
        static Heap* getInstance();
        virtual ~Heap();
        Heap(const Heap&) = delete;
        Heap& operator=(const Heap&) = delete;

        void setPath(std::string);
        std::string getPath() const;

        void runMain(Leitor*);
        void pushFrame(Frame*);
        void popFrame();
        Leitor* getClass(std::string);
        void loadClass(Leitor*);
        Frame* frameTop();
        Variable *getStaticInfo(std::string, std::string);
        JavaClassInstance* getInstantiatedClass(std::string);

        static void addStaticFields(JavaClassInstance*);
        static void addInstanceFields(JavaClassInstance*);
        
    private:
        Heap();
        static Heap* _heap;                                                         //!< Instância da classe Heap.
        std::string path;                                                           //!< Path para eventuais arquivos .class necessários para execução do programa Java.

        std::unordered_map<std::string, Leitor*>         _loadedClasses;         //!< Armazena as classes carregadas.
        std::unordered_map<std::string, JavaClassInstance*> _instantiatedClasses;   //!< Armazena as classes instânciadas.
        std::stack<Frame*>                                  _executionFrames;       //!< Pilha de Frames para execução.
};

/** \fn static Heap* Heap::getInstance()
 *  \brief Método responsável por retornar a instância de Heap, que é um Singleton.
 * 
 *  Durante a execução de um programa Java pela JVM, há uma área de memória reservada por alocar todos os dados: a Heap.
 *  A Heap segue o padrão de projeto Singleton e, portanto, só pode haver uma única instância durante a execução da JVM.
 *  O método getInstance() é responsável por retornar a única instância da Heap.
 * 
 *  \return Retorna a instância de Heap.
 */

/** \fn Heap::~Heap()
 *  \brief Destrutor da instância de Heap.
 * 
 *  É responsável por liberar a instância de Heap armazenada no ponteiro Heap::_heap.
 * 
 *  \return Nada é retornado.
 */

/** \fn Heap::Heap(const Heap&);
 *  \brief Método responsável por impedir a clonagem da instância de Heap.
 * 
 *  \param const Heap&; Endereço de uma variável tipo Heap
 *  \return Nada é retornado.
 */

/** \fn Heap& Heap::operator=(const Heap&)
 *  \brief Método responsável por impedir a clonagem da instância de Heap.
 * 
 *  \param const Heap&; Endereço de uma variável tipo Heap
 *  \return Nada é retornado.
 */

/** \fn void Heap::setPath(std::string path)
 *  \brief Método responsável por armazenar o caminho base dos arquivos do programa Java sendo executado.
 * 
 *  \param path; É uma std::string contendo o caminho base dos arquivos do programa Java sendo executado.
 *  \return Não retorna nada.
 */

/** \fn std::string Heap::getPath() const
 *  \brief Método responsável por retornar o caminho base dos arquivos do proograma Java sendo executado.
 *
 *  \return Retorna o caminho base dos arquivos do programa Java sendo executado.
 */

/** \fn void Heap::runMain(JavaClass *mainClass)
 *  \brief Método responsável por procurar o método "main" e executá-lo.
 * 
 *  O método runMain(JavaClass *mainClass) recebe a classe Java carregada, procura pelo método "main" na
 *  mesma e, caso encontre, chama a função de construção de Frame e inicia a execução do programa.
 * 
 *  \param *mainClass; Ponteiro para a classe Java carregada.
 *  \return Não retorna nada.
 */

/** \fn void Heap::pushFrame(Frame *frame)
 *  \brief Método responsável por empilhar um novo Frame na stack.
 * 
 *  \param *frame; Ponteiro para um Frame.
 *  \return Nada é retornado.
 */

/** \fn void Heap::popFrame()
 *  \brief Método responsável por desempilhar um Frame da stack.
 * 
 *  \return Nada é retornado.
 */

/** \fn JavaClass* Heap::getClass(std::string className)
 *  \brief Método responsável por retornar uma classe Java já carregada.
 * 
 *  O método getClass(std::string className) é responsável por buscar e retornar uma
 *  classe já carregada. Caso a classe - passada como parâmetro - não seja encontrada
 *  nas classes carregadas, o método JavaClass::readClassFile(std::string classFile)
 *  é chamado para tentar carregar a classe solicitada.
 *  Caso a classe seja lida, ela é carregada na Heap pelo método loadClass(JavaClass *jc).
 * 
 *  \param className; Uma std::string contendo o nome de uma classe.
 *  \return Retorna um ponteiro contendo uma classe Java carregada.
 */

/** \fn void Heap::loadClass(JavaClass *jc)
 *  \brief Método responsável por carregar classes Java na Heap.
 * 
 *  O método loadClass(JavaClass *jc) recebe um ponteiro de uma JavaClass que tenha sido lida,
 *  carrega a mesma na Heap, gera uma instância da classe - chamando o método
 *  addStaticFields(JavaClassInstance *_classInstance) -, e, após carga dos fields, a instância
 *  é carregada na Heap também.
 * 
 *  \param *jc; Ponteiro para uma classe Java lida.
 *  \return Nada é retornado.
 */

/** \fn static void Heap::addStaticFields(JavaClassInstance *_classInstance)
 *  \brief Método responsável por carregar os static Fields em uma instância de classe Java.
 * 
 *  O método addStaticFields(JavaClassInstance *_classInstance) carrega todos os Fields estáticos
 *  de uma classe Java sendo carregada na Heap. A carga ocorre para os Fields da própria classe,
 *  para os Fields que fazem referência a outras classes e para os Fields das superclasses - aqui
 *  de maneira recursiva até que se chegue na classe java/lang/Object.
 * 
 *  \param *_classInstance; Ponteiro para uma instância de classe Java.
 *  \return Nada é retornado.
 */

/** \fn static void Heap::addInstanceFields(JavaClassInstance *_classInstance)
 *  \brief Método responsável por carregar todos os Fields em uma instância de classe Java.
 * 
 *  O método addInstanceFields(JavaClassInstance *_classInstance) carrega todos os Fields
 *  de uma classe Java sendo carregada na Heap. A carga ocorre para os Fields da própria classe,
 *  para os Fields que fazem referência a outras classes e para os Fields das superclasses - aqui
 *  de maneira recursiva até que se chegue na classe java/lang/Object.
 * 
 *  \param *_classInstance; Ponteiro para uma instância de classe Java.
 *  \return Nada é retornado.
 */

/** \fn Heap::Heap()
 *  \brief Construtor padrão da classe.
 */

/** \fn Frame* Heap::frameTop()
 *  \brief Método responsável por retornar o Frame no topo da pilha.
 */

/** \fn Variable* Heap::getStaticInfo(std::string, std::string)
 *  \brief Método responsável por retornar os campos de uma classe estática.
 */

/** \fn JavaClassInstance* Heap::getInstantiatedClass(std::string)
 *  \brief Método responsável por retornar uma classe instanciada.
 */