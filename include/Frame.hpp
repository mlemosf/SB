#pragma once

#include "cp_info.hpp"
#include "attribute_info.hpp"
// #include "Structs.hpp"
#include "Types.hpp"

#include <sstream>
#include <vector>
#include <stack>

/** \class Frame
 *  \brief Define a estrutura e os métodos que compõe os frames de execução da Java Virtual Machine.
 * 
 *  A classe Frame é responsável por definir as estruturas e os métodos que compõe os frames de execução da
 *  Java Virtual Machine. Cada vez que um método é carregado, um novo Frame é construído e empilhado em uma área
 *  da Heap. Ao final da execução de cada método - natural ou abrupta - o Frame é destruído.
 */
class Frame {
    public:
        Frame(Leitor*, Cp_info*, u2, JavaClassInstance*, std::vector<Variable*>*);
        Frame(Leitor*, Cp_info*, u2, JavaClassInstance*);
        ~Frame();

        void                    executeFrame();
        static void             setOpcodes();
        static Variable*        constPoolRef(JavaClassInstance* jci, u2 index);         //!< Retorna valor do Runtime Constant Pool
        static void             newMultiDimensionalArray(arrayVariable *, std::stack < int >, std::string);
        void                    pushOpStack(std::stack<Variable*> *, Variable *);
        std::stack<Variable*>*  getStack();
    
    private:
        std::vector<Variable*>  _localVariables;    //!< Vetor de variáveis locais do Frame em execução.
        std::stack<Variable*>   _operandStack;      //!< Stack de operandos do Frame em execução.
        JavaClassInstance       *_classInstance;    //!< Instância da classe.
        Leitor                  *_jClass;           //!< Informação da classe.
        Attribute_info          *_code;             //!< Código do método associado ao Frame.
        Attribute_info          *_exceptions;       //!< Exceptions do método.
        u4                      _pc;                //!< Program Counter referente ao Frame em execução.
        u2                      _codeIndex;         //!< Código do método associado ao Frame.
        u2                      _methodIndex;       //!< Index do método.

        bool                    dbgpExecFlow = false; //!< Variavel para imprimir os PC e o opcode a cada instrução avaliada. Sigla: dbgp = (D)e(b)u(g)(p)rint
};

/** \fn Frame::Frame(JavaClass *jClass, cp_info *cp, u2 methodIndex, JavaClassInstance *jClassInstance, std::vector<Variable*> *args)
 *  \brief Construtor para Frame com argumentos.
 *  
 *  O construtor principal da classe Frame é responsável por preparar Frames que podem receber argumentos. O construtor busca na Constant Pool
 *  da classe Java pelo método que será carregado, as possíveis exceções associadas ao método, e define o tamanho do vetor de variáveis locais.
 * 
 *  \param *jClass; Ponteiro para classe Java carregada.
 *  \param *cp; Ponteiro para Constant Pool da classe Java carregada.
 *  \param *methodIndex; Entrada válida na Constant Pool da classe carregada que deve ser do tipo CONSTANT_Methodref_info.
 *  \param *jClassInstance; Ponteiro para instância da classe Java carregada.
 *  \param *args; Ponteiro para os argumentos do método sendo carregado.
 */

/** \fn Frame::Frame(JavaClass *jClass, cp_info *cp, u2 methodIndex, JavaClassInstance *jClassInstance)
 *  \brief Construtor para Frame do método main.
 *  
 *  O segundo construtor da classe Frame é responsável por preparar o Frame do método main do programa Java que será executado.
 *  Não precisa que os argumentos sejam passados na construção pois são acessados de acordo com os fields da classe ao qual o método main está
 *  associado.
 * 
 *  \param *jClass; Ponteiro para classe Java carregada.
 *  \param *cp; Ponteiro para Constant Pool da classe Java carregada.
 *  \param *methodIndex; Entrada válida na Constant Pool da classe carregada que deve ser do tipo CONSTANT_Methodref_info.
 *  \param *jClassInstance; Ponteiro para instância da classe Java carregada.
 */

/** \fn Frame::~Frame(...)
 *  \brief Destrutor para Frame
 */

/** \fn void Frame::executeFrame()
 *  \brief Método responsável pela execução do Frame.
 * 
 *  Acessa o vetor de funções e, a medida que o _pc avança, as próximas instruções são executadas.
 * 
 *  \return Não retorna nada.
 */

/** \fn static void Frame::setOpcodes()
 *  \brief Método responsável por definir as instruções em um vetor de funções.
 */

/** \fn void Frame::pushStackOp(std::stack<Variable*>, Variable*)
 *  \brief Método responsável por empilhar uma variável na stack do Frame atual.
 */

/** \fn std::stack<Variabel*> Frame::getStack()
 *  \brief Método responsável por retornar a stack do Frame atual.
 */

/** \fn static void Frame::newMultiDimensionalArray (arrayVariable *, std::stack< int >, std::string)
 *  \brief Método responsável pela criação de arrays multidimensionais.
 */