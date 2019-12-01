#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>

//! Define o tipo para tamanho de 1 byte.
typedef uint8_t     u1;
//! Define o tipo para tamanho de 2 bytes.
typedef uint16_t    u2;
//! Define o tipo para tamanho de 4 bytes.
typedef uint32_t    u4;
//! Define o tipo para tamanho de 8 bytes.
typedef uint64_t    u8;

typedef int8_t      s1;
typedef int16_t     s2;

//! Struct responsável por armazenar todo o Bytecode durante o loading.
/*!
    Ao ler um arquivo .class, a struct armazena cada byte do código fonte e
    possui um ponteiro para o próximo byte armazenado.
    Essa struct permite a alocação dinâmica de memória para carregar qualquer
    tamanho de arquivo .class.
*/
typedef struct bytecode {
    u1 byte;                //!< Armazena o n-ésimo byte do código fonte.
    struct bytecode *next;  //!< Ponteiro para o próximo byte do código fonte.
} bytecode;

//! Foward Declaration da classe JavaClass.
class Leitor;
//! Foward Declaration da union PrimitiveTypes.
union PrimitiveTypes;
//! Foward Declaration da struct JavaClassInstance.
struct JavaClassInstance;
//! Foward Declaration da struct arrayVariable.
struct arrayVariable;

/*! \class Variable
 *  \brief Define uma classe para armazenar as variáveis dos programas Java.
 * 
 * A classe define um enumerador para cada um dos tipos de dados possível na execução
 * de um programa Java (de 0 a 12). O valor do enumerador será associado a um atributo
 * tag que irá identificar cada instância da classe Variable.
 * Além disso, a classe contém uma union contendo: PrimitiveTypes - engloba todos os tipos
 * primitivos da linguagem Java -, arrayVariable - representa os arrays em Java -, JavaClassInstance
 * - representa um objeto Java -, std::string - representa as Strings -, e uint32_t - número de 32bits
 * sem sinal, que representa um endereço de retorno utilizado para operações de branch no Java assembly.
 * A classe possui dois construtores distintos: o primeiro, Variable::Variable(std::string descriptor), é
 * responsável por montar todas as variáveis definidas, o segundo, Variable::Variable(), é responsável
 * por construir uma variável void.
*/
class Variable {
    public:
        Variable(std::string descriptor, void* init_val);
        Variable(std::string descriptor) : Variable(descriptor, nullptr) {};
        Variable();

        enum type {_void, _byte, _bool, _char, _short, _int, _float,
            _long, _double, _classInstance, _array, _string, _returnAddress};   //!< Enumerador para o tipo de variável.
        
        type tag;                                                               //!< Armazena um número definido pelo Enumerador da classe. Varia entre 0 e 12, e define o tipo de variável
        union {
            PrimitiveTypes      *variable;                                      //!< Tipos primitivos da linguagem Java.
            arrayVariable       *array;                                         //!< Arrays Java.
            JavaClassInstance   *object;                                        //!< Objetos Java.
            std::string         *string;                                        //!< Strings Java.
            uint32_t            *returnAddress;                                 //!< Endereço de retorno - 32bits sem sinal - para instruções de branch Java assembly.
        };
};
/** \fn Variable::Variable(std::string descriptor)
 *  \brief Construtor da classe Variable.
 * 
 *  O construtor da classe é responsável por receber um argumento, tipo std::string, e com base nele, construir uma
 *  variável durante a execução do programa Java.
 * 
 *  \param descriptor; Uma std::string que define o tipo de variável que será construído para o programa Java sendo executado.
 *  \return Não retorna nada.
 */

/** \fn Variable::Variable()
 *  \brief Construtor alternativo da classe Variable.
 * 
 *  O construtor alternativo não recebe parâmetros e construi uma variável tipo void para o programa Java sendo executado.
 * 
 *  \return Não retorna nada.
 */

//! Union para os tipos primitivos Java.
/*!
    A union é responsável por armazenar os diferentes tipos primitivos de variáveis
    existentes na linguagem Java.
    Os tipos boolean, byte, char, short, int e float são representados por 32 bits
    sem sinal, e os tipos long e double são representados por 64bits sem sinal.
 */
typedef union PrimitiveTypes {
    uint32_t    *booleanValue;                                                  //!< Representação de um tipo Boolean.
    uint32_t    *byteValue;                                                     //!< Representação de um tipo Byte.
    uint32_t    *charValue;                                                     //!< Representação de um tipo Char.
    uint32_t    *shortValue;                                                    //!< Representação de um tipo Short.
    uint32_t    *intValue;                                                      //!< Representação de um tipo Integer.
    uint32_t    *floatValue;                                                    //!< Representação de um tipo Float
    uint64_t    *longValue;                                                     //!< Representação de um tipo Long.
    uint64_t    *doubleValue;                                                   //!< Representação de um tipo Double.
} PrimitiveTypes;

//! Struct responsável por armazenar uma instância de classe Java.
/*!
    A struct JavaClassInstance é responsável por armazenar instâncias de classes Java.
    A struct armazena as informações carregadas dos arquivos .class e os fields inicializados
    da classe.
 */
typedef struct JavaClassInstance {
    Leitor *javaClass;                                                       //!< Armazena as informações carregadas a partir de um arquivo .class
    std::unordered_map<std::string, Variable*> *fieldVariables;                 //!< Armazena os Fields inicializados da classe.
} JavaClassInstance;

//! Struct responsável por armazenar um array Java.
/*!
    A struct arrayVariable é responsável por armazenar os tipos Arrays das classes Java.
    Como o padrão de armazenamento do std::vector é do tipo Variable, podemos ter arrays
    multidimensionais, ou apenas arrays de tipos comuns.
 */
typedef struct arrayVariable {
    std::vector<Variable*>* array;                                              //!< Armazena um array de tipos Java.
} arrayVariable;

/**\fn Variable* copyVariable(Variable *_var)
 * \brief Método responsável por gerar uma cópia de uma dada variável fornecida como parâmetro.
 * 
 * \param *_var; Ponteiro para uma Variable.
 * \return Retorna o endereço da cópia criada.
*/
Variable* copyVariable(Variable *_var);