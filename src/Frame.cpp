#include "../include/Heap.hpp"
#include "../include/Frame.hpp"
#include "../include/leitor.hpp"
#include <math.h>
#include <string.h>

typedef void (*op_func_cb)(uint8_t* code, uint32_t* pc, std::stack<Variable*>* operandStack, std::vector<Variable*>* locals, Cp_info* constant_pool, JavaClassInstance* thisClass);

op_func_cb op_impl_set[256];

#define OPCODE_CB(val) op_impl_set[val] = [](u1 *code, u4 *pc, std::stack<Variable*> *operands, std::vector<Variable*> *localVariables, Cp_info *cp, JavaClassInstance *jClassInstance)
#define GETIMM(offset) code[(*pc)+offset]
#define PCINC(offset) *pc += offset
#define GETPC() *pc
#define SETPC(val) *pc = val
#define SIGNEXT(src,dest,by) (dest=1u<<(by-1), (src ^ dest) - dest)

#define CHECK_LV_REF(op_name, lv_var, lv_pos) if (lv_var == nullptr){ \
    throw std::runtime_error(op_name " cannot push a null reference from local variable area at " lv_pos); \
}
#define CHECK_LV_INT(op_name, lv_var, lv_pos) if (lv_var->tag != Variable::type::_int){ \
    throw std::runtime_error(op_name " local variable at " lv_pos " must be an integer"); \
}
#define CHECK_STACK_EMPTY() if (operands->empty()){ \
    throw std::runtime_error("StackUnderflowError"); \
}
#define CHECK_STACK_LEN(at_least) if(operands->size() < at_least){ \
    throw std::runtime_error("stack must contain at least " #at_least " elements."); \
}
#define POP_STACK() operands->pop()
#define STACK_TOP() operands->top()

// util functions
void check_variable_type(Variable *var, Variable::type vtype, std::string op_name, std::string who){
    // asm95@2018-12-04: this should be in security but yes, we need to know what's happening
    // switch cases are long because it was not programmed inside Variable class
    // see java basic types: https://docs.oracle.com/javase/tutorial/java/nutsandbolts/datatypes.html
    std::string type_repr = "<undefined>";

    switch(vtype){
        case Variable::type::_int:
            type_repr = "an integer"; break;
        case Variable::type::_long:
            type_repr = "a long"; break;
        case Variable::type::_float:
            type_repr = "a float"; break;
        case Variable::type::_double:
            type_repr = "a double"; break;
        default: break;
    }

    if (var->tag != vtype){
        throw std::runtime_error(
            op_name + ": " + who + " must be" + type_repr
        );
    }
}
void check_array_bounds(std::vector<Variable*> *vec, int index){
    // for some reason Java treats index as integers
    // to hide the compiler warning we cast size_t to int
    if (index < 0 || index >= (int)vec->size()){
        throw std::runtime_error(
            "array index (" + std::to_string(index) + ") out of bounds (0-" +
            std::to_string(vec->size()-1) + ")"
        );
    }
}

void Frame::setOpcodes(){
    OPCODE_CB(0x00){
        // NOP
        (*pc)++;
    };
    OPCODE_CB(0x01){
        // ACONST_NULL
        (*pc)++;

        operands->push(0);
    };
    OPCODE_CB(0x02){
        // ICONST_M1
        (*pc)++;

        Variable *var = new Variable("I");  // Cria uma variável tipo int
        *var->variable->intValue = -1;      // Variável recebe o valor -1
        operands->push(var);                // "Push" para a pilha de operandos
    };
    OPCODE_CB(0x03){
        // ICONST_0
        (*pc)++;

        Variable *var = new Variable("I");
        *var->variable->intValue = 0;
        operands->push(var);
    };
    OPCODE_CB(0x04){
        // ICONST_1
        (*pc)++;

        Variable *var = new Variable("I");
        *var->variable->intValue = 1;
        operands->push(var);
    };
    OPCODE_CB(0x05){
        // ICONST_2
        (*pc)++;

        Variable *var = new Variable("I");
        *var->variable->intValue = 2;
        operands->push(var);
    };
    OPCODE_CB(0x06){
        // ICONST_3
        (*pc)++;

        Variable *var = new Variable("I");
        *var->variable->intValue = 3;
        operands->push(var);
    };
    OPCODE_CB(0x07){
        // ICONST_4
        (*pc)++;
        
        Variable *var = new Variable("I");
        *var->variable->intValue = 4;
        operands->push(var);
    };
    OPCODE_CB(0x08){
        // ICONST_5
        (*pc)++;

        Variable *var = new Variable("I");
        *var->variable->intValue = 5;
        operands->push(var);
    };
    OPCODE_CB(0x09){
        // LCONST_0
        (*pc)++;

        Variable *var = new Variable("J");
        *var->variable->longValue = 0;
        operands->push(var);
    };
    OPCODE_CB(0x0A){
        // LCONST_1
        (*pc)++;

        Variable *var = new Variable("J");
        *var->variable->longValue = 1;
        operands->push(var);
    };
    OPCODE_CB(0x0B){
        // FCONST_0
        (*pc)++;

        Variable *var = new Variable("F");
        float value = 0.0f;
        *((float*)var->variable->floatValue) = value;
        operands->push(var);
    };
    OPCODE_CB(0x0C){
        // FCONST_1
        (*pc)++;

        Variable *var = new Variable("F");
        float value = (float)1.0f;
        *((float*)var->variable->floatValue) = value;
        operands->push(var);
    };
    OPCODE_CB(0x0D){
        // FCONST_2
        (*pc)++;

        Variable *var = new Variable("F");
        float value = (float)2.0f;
        *((float*)var->variable->floatValue) = value;
        operands->push(var);
    };
    OPCODE_CB(0x0E){
        // DCONST_0
        (*pc)++;

        Variable *var = new Variable("D");
        double value = 0.0f;
        *((double*)var->variable->doubleValue) = value;
        operands->push(var);
    };
    OPCODE_CB(0x0F){
        // DCONST_1
        (*pc)++;

        Variable *var = new Variable("D");
        double value = 1.0f;
        *((double*)var->variable->doubleValue) = value;
        operands->push(var);
    };
    OPCODE_CB(0x10){
        // BIPUSH
        u1 byteValue = GETIMM(1);
        PCINC(2);

        u4 aux;
        aux = SIGNEXT(byteValue, aux, 8);

        Variable *var = new Variable("I");
        *var->variable->intValue = aux;
        operands->push(var);
    };
    OPCODE_CB(0x11){
        // SIPUSH
        u2 shortValue = ((u2)GETIMM(1) << 8 | GETIMM(2));
        PCINC(3);

        u4 aux;
        aux = SIGNEXT(shortValue, aux, 16);

        Variable *var = new Variable("I");
        *var->variable->intValue = aux;
        operands->push(var);
    };
    OPCODE_CB(0x12){
        // LDC
        u1 CPIndex = GETIMM(1);
        PCINC(2);

        // resolution process (5.4.3)
        Variable *var = Frame::constPoolRef(jClassInstance, CPIndex);
        operands->push(var);
    };
    OPCODE_CB(0x13){
        // LDC_W
        u2 CPWideIndex = ((u2)GETIMM(1) << 8 | GETIMM(2));
        PCINC(3);

        // resolution process (5.4.3)
        Variable *var = Frame::constPoolRef(jClassInstance, CPWideIndex);
        operands->push(var);
    };
    OPCODE_CB(0x14){
        // LDC2_W
        u2 CPWideIndex = ((u2)GETIMM(1) << 8 | GETIMM(2));
        PCINC(3);

        Variable *var = Frame::constPoolRef(jClassInstance, CPWideIndex);
        operands->push(var);
    };
    OPCODE_CB(0x15){
        // ILOAD
        (*pc)++;

        uint8_t idx = code[(*pc)++];
        operands->push((*localVariables)[idx]);
    };
    OPCODE_CB(0x16){
        // LLOAD
        (*pc)++;

        uint8_t idx = code[(*pc)++];
        operands->push((*localVariables)[idx]);
    };
    OPCODE_CB(0x17){
        // FLOAD
        (*pc)++;

        uint8_t idx = code[(*pc)++];
        operands->push((*localVariables)[idx]);
    };
    OPCODE_CB(0x18){
        // DLOAD
        (*pc)++;

        uint8_t idx = code[(*pc)++];
        operands->push((*localVariables)[idx]);
    };
    OPCODE_CB(0x19){
        // ALOAD
        (*pc)++;

        uint8_t idx = code[(*pc)++];
        operands->push((*localVariables)[idx]);
    };
    OPCODE_CB(0x1A){
        // ILOAD_0
        PCINC(1);
        Variable *localVarAt = localVariables->at(0);

        CHECK_LV_REF("ILOAD_0", localVarAt, "0");
        // CHECK_LV_INT("ILOAD_0", localVarAt, "0");

		Variable *toLoad = copyVariable(localVarAt);

        operands->push(toLoad);
    };
    OPCODE_CB(0x1B){
        // ILOAD_1
        PCINC(1);
        Variable *localVarAt = localVariables->at(1);

        CHECK_LV_REF("ILOAD_1", localVarAt, "1");
        // CHECK_LV_INT("ILOAD_1", localVarAt, "1");

		Variable *toLoad = copyVariable(localVarAt);

        operands->push(toLoad);
    };
    OPCODE_CB(0x1C){
        // ILOAD_2
        PCINC(1);
        Variable *localVarAt = localVariables->at(2);

        CHECK_LV_REF("ILOAD_2", localVarAt, "2");
        // CHECK_LV_INT("ILOAD_2", localVarAt, "2");

		Variable *toLoad = copyVariable(localVarAt);

        operands->push(toLoad);
    };
    OPCODE_CB(0x1D){
        // ILOAD_3
        PCINC(1);
        Variable *localVarAt = localVariables->at(3);

        CHECK_LV_REF("ILOAD_3", localVarAt, "3");
        // CHECK_LV_INT("ILOAD_3", localVarAt, "3");

		Variable *toLoad = copyVariable(localVarAt);

        operands->push(toLoad);
    };
    OPCODE_CB(0x1E){
        // LLOAD_0
        (*pc)++;
        operands->push((*localVariables)[0]);
    };
    OPCODE_CB(0x1F){
        // LLOAD_1
        (*pc)++;
        operands->push((*localVariables)[1]);
    };
    OPCODE_CB(0x20){
        // LLOAD_2
        (*pc)++;
        operands->push((*localVariables)[2]);
    };
    OPCODE_CB(0x21){
        // LLOAD_3
        (*pc)++;
        operands->push((*localVariables)[3]);
    };
    OPCODE_CB(0x22){
        // FLOAD_0
        (*pc)++;
        operands->push((*localVariables)[0]);
    };
    OPCODE_CB(0x23){
        // FLOAD_1
        (*pc)++;
        operands->push((*localVariables)[1]);
    };
    OPCODE_CB(0x24){
        // FLOAD_2
        (*pc)++;
        operands->push((*localVariables)[2]);
    };
    OPCODE_CB(0x25){
        // FLOAD_3
        (*pc)++;
        operands->push((*localVariables)[3]);
    };
    OPCODE_CB(0x26){
        // DLOAD_0
        PCINC(1);
        operands->push((*localVariables)[0]);
    };
    OPCODE_CB(0x27){
        // DLOAD_1
        PCINC(1);
        Variable *doubleValue = localVariables->at(1);
        operands->push(doubleValue);
    };
    OPCODE_CB(0x28){
        // DLOAD_2
        PCINC(1);
        operands->push((*localVariables)[2]);
    };
    OPCODE_CB(0x29){
        // DLOAD_3
        PCINC(1);
        operands->push((*localVariables)[3]);
    };
    OPCODE_CB(0x2A){
        // ALOAD_0
        (*pc)++;
        operands->push(localVariables->at(0));
    };
    OPCODE_CB(0x2B){
        // ALOAD_1
        (*pc)++;
        operands->push((*localVariables)[1]);
    };
    OPCODE_CB(0x2C){
        // ALOAD_2
        (*pc)++;
        operands->push((*localVariables)[2]);
    };
    OPCODE_CB(0x2D){
        // ALOAD_3
        (*pc)++;
        operands->push((*localVariables)[3]);
    };
    OPCODE_CB(0x2E){
        // IALOAD
        (*pc)++;

        Variable *idx = operands->top();
        operands->pop();
        Variable *ref = operands->top();
        operands->pop();

        operands->push((*ref->array->array)[*idx->variable->intValue]);
    };
    OPCODE_CB(0x2F){
        // LALOAD
        (*pc)++;

        Variable *idx = operands->top();
        operands->pop();
        Variable *ref = operands->top();
        operands->pop();

        operands->push((*ref->array->array)[*idx->variable->intValue]);
    };
    OPCODE_CB(0x30){
        // FALOAD
        (*pc)++;

        Variable *idx = operands->top();
        operands->pop();
        Variable *ref = operands->top();
        operands->pop();

        operands->push((*ref->array->array)[*idx->variable->intValue]);
    };
    OPCODE_CB(0x31){
        // DALOAD
        (*pc)++;

        Variable *idx = operands->top();
        operands->pop();
        Variable *ref = operands->top();
        operands->pop();

        operands->push((*ref->array->array)[*idx->variable->intValue]);
    };
    OPCODE_CB(0x32){
        // AALOAD
        (*pc)++;

        Variable *idx = operands->top();
        operands->pop();
        Variable *ref = operands->top();
        operands->pop();

        operands->push((*ref->array->array)[*idx->variable->intValue]);
        std::cout << "teste";
    };
    OPCODE_CB(0x33){
        // BALOAD
        (*pc)++;

        Variable *idx = operands->top();
        operands->pop();
        Variable *ref = operands->top();
        operands->pop();

        int varAt = *(int*)idx->variable->intValue;
        Variable *theValue = ref->array->array->at(varAt);

        operands->push(theValue);
    };
    OPCODE_CB(0x34){
        // CALOAD
        (*pc)++;

        Variable *idx = operands->top();
        operands->pop();
        Variable *ref = operands->top();
        operands->pop();

        operands->push((*ref->array->array)[*idx->variable->intValue]);
    };
    OPCODE_CB(0x35){
        // SALOAD
        (*pc)++;

        Variable *idx = operands->top();
        operands->pop();
        Variable *ref = operands->top();
        operands->pop();

        operands->push((*ref->array->array)[*idx->variable->intValue]);
    };
    OPCODE_CB(0x36){
        // ISTORE
        (*pc)++;

        uint8_t idx = *(code + (*pc)++);
        (*localVariables)[idx] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x37){
        // LSTORE
        (*pc)++;

        uint8_t idx = *(code + (*pc)++);
        (*localVariables)[idx] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x38){
        // FSTORE
        (*pc)++;

        uint8_t idx = *(code + (*pc)++);
        (*localVariables)[idx] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x39){
        // DSTORE
        PCINC(1);

        uint8_t idx = *(code + (*pc)++);
        (*localVariables)[idx] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x3A){
        // ASTORE
        (*pc)++;

        uint8_t idx = *(code + (*pc)++);
        (*localVariables)[idx] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x3B){
        // ISTORE_0
        (*pc)++;
        (*localVariables)[0] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x3C){
        // ISTORE_1
		(*pc)++;
		Variable* value = operands->top();
		operands->pop();
        localVariables->at(1) = value;
    };
    OPCODE_CB(0x3D){
        // ISTORE_2
		(*pc)++;
		Variable* value = operands->top();
		operands->pop();
        localVariables->at(2) = value;
    };
    OPCODE_CB(0x3E){
        // ISTORE_1
		(*pc)++;
		Variable* value = operands->top();
		operands->pop();
        localVariables->at(3) = value;
    };
    OPCODE_CB(0x3F){
        // LSTORE_0
        (*pc)++;
        (*localVariables)[0] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x40){
        // LSTORE_1
        (*pc)++;
        (*localVariables)[1] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x41){
        // LSTORE_2
        (*pc)++;
        (*localVariables)[2] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x42){
        // LSTORE_3
        (*pc)++;
        (*localVariables)[3] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x43){
        // FSTORE_0
        (*pc)++;
        (*localVariables)[0] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x44){
        // FSTORE_1
        (*pc)++;
        (*localVariables)[1] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x45){
        // FSTORE_2
        (*pc)++;
        (*localVariables)[2] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x46){
        // FSTORE_3
        (*pc)++;
        (*localVariables)[3] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x47){
        // DSTORE_0
        (*pc)++;
        (*localVariables)[0] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x48){
        // DSTORE_1
        (*pc)++;
        Variable *TopStackDouble = operands->top();
        (*localVariables)[1] = TopStackDouble;
        operands->pop();
    };
    OPCODE_CB(0x49){
        // DSTORE_2
        (*pc)++;
        (*localVariables)[2] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x4A){
        // DSTORE_3
        (*pc)++;
        (*localVariables)[3] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x4B){
        // ASTORE_0
        (*pc)++;
        (*localVariables)[0] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x4C){
        // ASTORE_1
        (*pc)++;
        (*localVariables)[1] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x4D){
        // ASTORE_2
        (*pc)++;
        (*localVariables)[2] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x4E){
        // ASTORE_3
        (*pc)++;
        (*localVariables)[3] = operands->top();
        operands->pop();
    };
    OPCODE_CB(0x4F){
        // IASTORE
        (*pc)++;

        Variable *val = operands->top();
        operands->pop();
        Variable *idx = operands->top();
        operands->pop();
        Variable *ref = operands->top();
        operands->pop();

        Variable *aux = new Variable("I");
        *aux->variable->intValue = *val->variable->intValue;
        (*ref->array->array)[*idx->variable->intValue] = aux;
    };
    OPCODE_CB(0x50){
        // LASTORE
        (*pc)++;

        Variable *val = operands->top();
        operands->pop();
        Variable *idx = operands->top();
        operands->pop();
        Variable *ref = operands->top();
        operands->pop();

        Variable *aux = new Variable("J");
        *aux->variable->longValue = *val->variable->longValue;
        (*ref->array->array)[*idx->variable->intValue] = aux;
    };
    OPCODE_CB(0x51){
        // FASTORE
        (*pc)++;

        Variable *val = operands->top();
        operands->pop();
        Variable *idx = operands->top();
        operands->pop();
        Variable *ref = operands->top();
        operands->pop();

        Variable *aux = new Variable("F");
        *aux->variable->floatValue = *val->variable->floatValue;
        (*ref->array->array)[*idx->variable->intValue] = aux;
    };
    OPCODE_CB(0x52){
        // DASTORE
        (*pc)++;

        Variable *val = operands->top();
        operands->pop();
        Variable *idx = operands->top();
        operands->pop();
        Variable *ref = operands->top();
        operands->pop();

        Variable *aux = new Variable("D");
        *aux->variable->doubleValue = *val->variable->doubleValue;
        (*ref->array->array)[*idx->variable->intValue] = aux;
    };
    OPCODE_CB(0x53){
        // AASTORE
        (*pc)++;

        Variable *val = operands->top();
        operands->pop();
        Variable *idx = operands->top();
        operands->pop();
        Variable *ref = operands->top();
        operands->pop();

        Variable *aux = new Variable("[");
        *aux->array->array = *val->array->array;
        (*ref->array->array)[*idx->variable->intValue] = aux;
    };
    OPCODE_CB(0x54){
        // BASTORE
        (*pc)++;

        CHECK_STACK_LEN(3);
        Variable *val = operands->top();
        operands->pop();
        Variable *idx = operands->top();
        operands->pop();
        Variable *ref = operands->top();
        operands->pop();

        // TODO@2018-12-04: check if ref is an reference
        check_variable_type(idx, Variable::type::_int, "BASTORE", "index");
        check_variable_type(val, Variable::type::_int, "BASTORE", "value");

        Variable *aux = new Variable("B", val->variable->intValue);
        int theIndex = *((int*)idx->variable->intValue);
        // the int value must be truncated to signed byte and store in the array
        check_array_bounds(ref->array->array, theIndex);
        (*ref->array->array)[theIndex] = aux;
    };
    OPCODE_CB(0x55){
        // CASTORE
        (*pc)++;

        Variable *val = operands->top();
        operands->pop();
        Variable *idx = operands->top();
        operands->pop();
        Variable *ref = operands->top();
        operands->pop();

        Variable *aux = new Variable("C");
        *aux->variable->charValue = *val->variable->charValue;
        (*ref->array->array)[*idx->variable->charValue] = aux;
    };
    OPCODE_CB(0x56){
        // SASTORE
        (*pc)++;

        Variable *val = operands->top();
        operands->pop();
        Variable *idx = operands->top();
        operands->pop();
        Variable *ref = operands->top();
        operands->pop();

        Variable *aux = new Variable("S");
        *aux->variable->shortValue = *val->variable->shortValue;
        (*ref->array->array)[*idx->variable->shortValue] = aux;
    };
    OPCODE_CB(0x57){
        // POP
        PCINC(1);
        // TODO WARNING: pop should remove slots from the operand stack (OS), not actual variables
        CHECK_STACK_EMPTY();
        POP_STACK();
    };
    OPCODE_CB(0x58){
        // POP2
        PCINC(1);
        CHECK_STACK_EMPTY();
        Variable* value = STACK_TOP();
        POP_STACK();
        if (value->tag != Variable::type::_double || value->tag != Variable::type::_long){
            // they are category 1, so "two slots" will be removed
            CHECK_STACK_EMPTY();
            POP_STACK();
        }
    };
    OPCODE_CB(0x59){
        // DUP
        (*pc)++;

        Variable *dup = operands->top();
        operands->push(dup);
    };
    OPCODE_CB(0x5A){
        // DUP_X1
        (*pc)++;

        Variable *dup1 = operands->top();
        operands->pop();
        Variable *dup2 = operands->top();
        operands->pop();

        if (dup1->tag == Variable::_double || dup1->tag == Variable::_long || dup2->tag == Variable::_double || dup1->tag == Variable::_long) {
            operands->push(dup2);
            operands->push(dup1);
        }
        else {
            operands->push(copyVariable(dup1));
            operands->push(dup2);
            operands->push(dup1);
        }
    };
    OPCODE_CB(0x5B){
        // DUP_X2
        (*pc)++;

        Variable *dup1 = operands->top();
        operands->pop();
        Variable *dup2 = operands->top();
        operands->pop();

        if (dup1->tag == Variable::_double || dup1->tag == Variable::_long || dup2->tag == Variable::_double || dup1->tag == Variable::_long) {
            operands->push(copyVariable(dup1));
            operands->push(dup2);
            operands->push(dup1);
        }
        else {
            Variable *dup3 = operands->top();
            operands->pop();

            if (dup3->tag == Variable::_double || dup3->tag == Variable::_long) {
                operands->push(copyVariable(dup1));
                operands->push(dup3);
                operands->push(dup2);
                operands->push(dup1);
            }
        }
    };
    OPCODE_CB(0x5C){
        // DUP2
        (*pc)++;

        Variable *dup1 = operands->top();
        operands->pop();

        if (dup1->tag == Variable::_double || dup1->tag == Variable::_long) {
            Variable *dup2 = operands->top();
            operands->pop();

            operands->push(copyVariable(dup2));
            operands->push(copyVariable(dup1));
            operands->push(dup2);
            operands->push(dup1);
        }
        else {
            operands->push(copyVariable(dup1));
            operands->push(dup1);
        }
    };
    OPCODE_CB(0x5D){
        // DUP2_X1
        (*pc)++;

        Variable *dup1 = operands->top();
        operands->pop();
        Variable *dup2 = operands->top();
        operands->pop();

        if (dup1->tag == Variable::_double || dup1->tag == Variable::_long) {
            Variable *dup3 = operands->top();
            operands->pop();

            operands->push(copyVariable(dup2));
            operands->push(copyVariable(dup1));
            operands->push(dup3);
            operands->push(dup2);
            operands->push(dup1);
        }
        else {
            operands->push(copyVariable(dup1));
            operands->push(dup2);
            operands->push(dup1);
        }
    };
    OPCODE_CB(0x5E){
        // DUP2_X2
        (*pc)++;

        Variable *dup1 = operands->top();
        operands->pop();
        Variable *dup2 = operands->top();
        operands->pop();

        if (dup1->tag == Variable::_double || dup1->tag == Variable::_long || dup2->tag == Variable::_double || dup1->tag == Variable::_long) {
            Variable *dup3 = operands->top();
            operands->pop();

            if (dup3->tag == Variable::_double || dup3->tag == Variable::_long) {
                Variable *dup4 = operands->top();
                operands->pop();

                operands->push(copyVariable(dup2));
                operands->push(copyVariable(dup1));
                operands->push(dup4);
                operands->push(dup3);
                operands->push(dup2);
                operands->push(dup1);
            }
            else {
                operands->push(copyVariable(dup2));
                operands->push(copyVariable(dup1));
                operands->push(dup3);
                operands->push(dup2);
                operands->push(dup1);
            }
        }
        else {
            if (dup2->tag == Variable::_double || dup2->tag == Variable::_long) {
                operands->push(copyVariable(dup1));
                operands->push(dup2);
                operands->push(dup1);
            }
            else {
                Variable *dup3 = operands->top();
                operands->pop();

                operands->push(copyVariable(dup1));
                operands->push(dup3);
                operands->push(dup2);
                operands->push(dup1);
            }
        }
    };
    OPCODE_CB(0x5F){
        // SWAP
        (*pc)++;

        Variable *sw1 = operands->top();
        operands->pop();
        Variable *sw2 = operands->top();
        operands->pop();

        operands->push(sw1);
        operands->push(sw2);
    };
    OPCODE_CB(0x60){
        // IADD
        (*pc)++;

        Variable *v1 = operands->top();
        operands->pop();
        Variable *v2 = operands->top();
        operands->pop();

        Variable *v3 = new Variable("I");
        *((int *) v3->variable->intValue) = *((int *) v1->variable->intValue) + *((int *) v2->variable->intValue);
        operands->push(v3);
    };
    OPCODE_CB(0x61){
        // LADD
        (*pc)++;

        Variable *v1 = operands->top();
        operands->pop();
        long long s1 = *((long long*)v1->variable->longValue);
        Variable *v2 = operands->top();
        long long s2 = *((long long*)v2->variable->longValue);
        operands->pop();

        Variable *v3 = new Variable("J");
        long long soma = s2+s1;
        *((long long*) v3->variable->longValue) = soma;
        operands->push(v3);
    };
    OPCODE_CB(0x62){
        // FADD
        (*pc)++;

        Variable *v1 = operands->top();
        operands->pop();
        float s1 = *((float*)v1->variable->floatValue);
        Variable *v2 = operands->top();
        float s2 = *((float*)v2->variable->floatValue);
        operands->pop();

        Variable *v3 = new Variable("F");
        float soma = s2+s1;
        *((float *) v3->variable->floatValue) = soma;
        operands->push(v3);
    };
    OPCODE_CB(0x63){
        // DADD
        PCINC(1);

        Variable *v1 = operands->top();
        operands->pop();
        double s1 = *((double*)v1->variable->doubleValue);
        Variable *v2 = operands->top();
        double s2 = *((double*)v2->variable->doubleValue);
        operands->pop();

        Variable *v3 = new Variable("D");
        double soma = s2+s1;
        *((double*)v3->variable->doubleValue) = soma;
        operands->push(v3);
    };
    OPCODE_CB(0x64){
        // ISUB
        (*pc)++;

        Variable *v1 = operands->top();
        operands->pop();
        Variable *v2 = operands->top();
        operands->pop();

        Variable *v3 = new Variable("I");
        *((int *) v3->variable->intValue) = *((int *) v2->variable->intValue) - *((int *) v1->variable->intValue);
        operands->push(v3);
    };
    OPCODE_CB(0x65){
        // LSUB
        (*pc)++;

        Variable *v1 = operands->top();
        long long s1 = *((long long*)v1->variable->longValue);
        operands->pop();
        Variable *v2 = operands->top();
        long long s2 = *((long long*)v2->variable->longValue);
        operands->pop();

        Variable *v3 = new Variable("J");
        long long sub = s2-s1;
        *((long long*) v3->variable->longValue) = sub;
        operands->push(v3);
    };
    OPCODE_CB(0x66){
        // FSUB
        (*pc)++;

        Variable *v1 = operands->top();
        float s1 = *((float*)v1->variable->floatValue);
        operands->pop();
        Variable *v2 = operands->top();
        float s2 = *((float*)v2->variable->floatValue);
        operands->pop();

        Variable *v3 = new Variable("F");
        float sub = s2-s1;
        *((float *) v3->variable->floatValue) = sub;
        operands->push(v3);
    };
    OPCODE_CB(0x67){
        // DSUB
        PCINC(1);

        Variable *v1 = operands->top();
        double s1 = *((double*)v1->variable->doubleValue);
        operands->pop();
        Variable *v2 = operands->top();
        double s2 = *((double*)v2->variable->doubleValue);
        operands->pop();

        Variable *v3 = new Variable("D");
        double sub = s2-s1;
        *((double*)v3->variable->doubleValue) = sub;
        operands->push(v3);
    };
    OPCODE_CB(0x68){
        // IMUL
        (*pc)++;

        Variable *var1 = operands->top();
        operands->pop();
        Variable *var2 = operands->top();
        operands->pop();

        Variable *res = new Variable("I");
        *((int *) res->variable->intValue) = *((int *) var1->variable->intValue) * *((int *) var2->variable->intValue);
        operands->push(res);
    };
    OPCODE_CB(0x69){
        // LMUL
        (*pc)++;

        Variable *var1 = operands->top();
        long long s1 = *((long long*)var1->variable->longValue);
        operands->pop();
        Variable *var2 = operands->top();
        long long s2 = *((long long*)var2->variable->longValue);
        operands->pop();

        Variable *res = new Variable("J");
        long long mul = s2*s1;
        *((long long*) res->variable->longValue) = mul;
        operands->push(res);
    };
    OPCODE_CB(0x6A){
        // FMUL
        (*pc)++;

        Variable *var1 = operands->top();
        float s1 = *((float*)var1->variable->floatValue);
        operands->pop();
        Variable *var2 = operands->top();
        float s2 = *((float*)var2->variable->floatValue);
        operands->pop();

        Variable *res = new Variable("F");
        float mul = s2*s1;
        *((float *) res->variable->floatValue) = mul;
        operands->push(res);
    };
    OPCODE_CB(0x6B){
        // DMUL
        PCINC(1);

        Variable *v1 = operands->top();
        double s1 = *((double*)v1->variable->doubleValue);
        operands->pop();
        Variable *v2 = operands->top();
        double s2 = *((double*)v2->variable->doubleValue);
        operands->pop();

        Variable *v3 = new Variable("D");
        double mul = s2*s1;
        *((double*)v3->variable->doubleValue) = mul;
        operands->push(v3);
    };
    OPCODE_CB(0x6C){
        // IDIV
        (*pc)++;

        Variable *var1 = operands->top();
        operands->pop();
        Variable *var2 = operands->top();
        operands->pop();

        Variable *res = new Variable("I");
        *((int *) res->variable->intValue) = *((int *) var2->variable->intValue) / *((int *) var1->variable->intValue);
        operands->push(res);
    };
    OPCODE_CB(0x6D){
        // LDIV
        (*pc)++;

        Variable *var1 = operands->top();
        long long s1 = *((long long*)var1->variable->longValue);
        operands->pop();
        Variable *var2 = operands->top();
        long long s2 = *((long long*)var2->variable->longValue);
        operands->pop();

        Variable *res = new Variable("J");
        long long _div = s2/s1;
        *((long long*) res->variable->longValue) = _div;
        operands->push(res);
    };
    OPCODE_CB(0x6E){
        // FDIV
        (*pc)++;

        Variable *var1 = operands->top();
        float s1 = *((float*)var1->variable->floatValue);
        operands->pop();
        Variable *var2 = operands->top();
        float s2 = *((float*)var2->variable->floatValue);
        operands->pop();

        Variable *res = new Variable("F");
        float _div = s2/s1;
        *((float *) res->variable->floatValue) = _div;
        operands->push(res);
    };
    OPCODE_CB(0x6F){
        // DDIV
        PCINC(1);

        Variable *v1 = operands->top();
        double s1 = *((double*)v1->variable->doubleValue);
        operands->pop();
        Variable *v2 = operands->top();
        double s2 = *((double*)v2->variable->doubleValue);
        operands->pop();

        Variable *v3 = new Variable("D");
        double _div = s2/s1;
        *((double*)v3->variable->doubleValue) = _div;
        operands->push(v3);
        
    };
    OPCODE_CB(0x70){
        // IREM
        (*pc)++;

        Variable *var1 = operands->top();
        operands->pop();
        Variable *var2 = operands->top();
        operands->pop();

        Variable *res = new Variable("I");
        *((int *) res->variable->intValue) = *((int *) var2->variable->intValue) %  *((int *) var1->variable->intValue);
        operands->push(res);
    };
    OPCODE_CB(0x71){
        // LREM
        (*pc)++;

        Variable *var1 = operands->top();
        operands->pop();
        long long s1 = *((long long*)var1->variable->longValue);
        Variable *var2 = operands->top();
        long long s2 = *((long long*)var2->variable->longValue);
        operands->pop();

        Variable *res = new Variable("J");
        long long mod = s2%s1;
        *((long long*) res->variable->longValue) = mod;
        operands->push(res);
    };
    OPCODE_CB(0x72){
        // FREM
        (*pc)++;

        Variable *var1 = operands->top();
        float s1 = *((float*)var1->variable->floatValue);
        operands->pop();
        Variable *var2 = operands->top();
        float s2 = *((float*)var2->variable->floatValue);
        operands->pop();

        Variable *res = new Variable("F");
        float mod = fmod(s2, s1);
        (*((float *) res->variable->floatValue)) = mod;
        operands->push(res);
    };
    OPCODE_CB(0x73){
        // DREM
        PCINC(1);

        Variable *v1 = operands->top();
        double s1 = *((double*)v1->variable->doubleValue);
        operands->pop();
        Variable *v2 = operands->top();
        double s2 = *((double*)v2->variable->doubleValue);
        operands->pop();

        Variable *v3 = new Variable("D");
        double mod = fmod(s2, s1);
        *((double*)v3->variable->doubleValue) = mod;
        operands->push(v3);
    };
    OPCODE_CB(0x74){
        // INEG
        (*pc)++;

        Variable *var = operands->top();
        operands->pop();

        Variable *res = new Variable("I");
        (*((int *) res->variable->intValue)) = -(*((int *) var->variable->intValue));
        operands->push(res);
    };
    OPCODE_CB(0x75){
        // LNEG
        (*pc)++;

        Variable *var = operands->top();
        long long neg = *((long long*)var->variable->longValue);
        operands->pop();

        Variable *res = new Variable("J");
        *((long long*) res->variable->longValue) = -(neg);
        operands->push(res);
    };
    OPCODE_CB(0x76){
        // FNEG
        (*pc)++;

        Variable *var = operands->top();
        float neg = *((float*)var->variable->floatValue);
        operands->pop();

        Variable *res = new Variable("F");
        *((float *) res->variable->floatValue) = -(neg);
        operands->push(res);
    };
    OPCODE_CB(0x77){
        // DNEG
        PCINC(1);

        Variable *v1 = operands->top();
        double neg = *((double*)v1->variable->doubleValue);
        operands->pop();

        Variable *v3 = new Variable("D");
        *((double*)v3->variable->doubleValue) = -(neg);
        operands->push(v3);
    };
    OPCODE_CB(0x78){
        // ISHL
        (*pc)++;

        Variable *var2 = operands->top();
        operands->pop();
        Variable *var1 = operands->top();
        operands->pop();

        Variable *res = new Variable("I");
        *((int *) res->variable->intValue) = *((int *) var1->variable->intValue) << (*((int *) var2->variable->intValue) & 0x1F);
        operands->push(res);
    };
    OPCODE_CB(0x79){
        // LSHL
        (*pc)++;

        Variable *var2 = operands->top();
        long long s1 = *((long long*)var2->variable->longValue);
        operands->pop();
        Variable *var1 = operands->top();
        long long s2 = *((long long*)var1->variable->longValue);
        operands->pop();

        Variable *res = new Variable("J");
        long long shift = s2 << (s1 & 0x3F);
        *((long long*) res->variable->longValue) = shift;
        operands->push(res);
    };
    OPCODE_CB(0x7A){
        // ISHR
        (*pc)++;

        Variable *var2 = operands->top();
        operands->pop();
        Variable *var1 = operands->top();
        operands->pop();

        Variable *res = new Variable("I");
        int s = *((int *) var2->variable->intValue) & 0x1F;
        *((int *) res->variable->intValue) = *((int *) var1->variable->intValue) / (0x01 << s);
        operands->push(res);
    };
    OPCODE_CB(0x7B){
        // LSHR
        (*pc)++;

        Variable *var2 = operands->top();
        operands->pop();
        Variable *var1 = operands->top();
        operands->pop();

        Variable *res = new Variable("J");
        int s = *((int *) var2->variable->intValue) & 0x3F;
        *((long *) res->variable->longValue) = *((long *) var1->variable->longValue) / (0x01 << s);
        operands->push(res);
    };
    OPCODE_CB(0x7C){
        // IUSHR
        (*pc)++;

        Variable *var2 = operands->top();
        operands->pop();
        Variable *var1 = operands->top();
        operands->pop();

        Variable *res = new Variable("I");
        *((int *) res->variable->intValue) = *((int *) var1->variable->intValue) >> (*((int *) var2->variable->intValue) & 0x1F);
        operands->push(res);
    };
    OPCODE_CB(0x7D){
        // LUSHR
        (*pc)++;

        Variable *var2 = operands->top();
        operands->pop();
        Variable *var1 = operands->top();
        operands->pop();

        Variable *res = new Variable("J");
        *((long *) res->variable->longValue) = *((long *) var1->variable->longValue) >> (*((int *) var2->variable->intValue) & 0x3F);
        operands->push(res);
    };
    OPCODE_CB(0x7E){
        // IAND
        (*pc)++;

        Variable *var1 = operands->top();
        operands->pop();
        Variable *var2 = operands->top();
        operands->pop();

        Variable *res = new Variable("I");
        *((int *) res->variable->intValue) = *((int *) var1->variable->intValue) & *((int *) var2->variable->intValue);
        operands->push(res);
    };
    OPCODE_CB(0x7F){
        // LAND
        (*pc)++;

        Variable *var1 = operands->top();
        long long s1 = *((long long*)var1->variable->longValue);
        operands->pop();
        Variable *var2 = operands->top();
        long long s2 = *((long long*)var2->variable->longValue);
        operands->pop();

        Variable *res = new Variable("J");
        long long _and = s2 & s1;
        *((long long*) res->variable->longValue) = _and;
        operands->push(res);
    };
    OPCODE_CB(0x80){
        // IOR
        (*pc)++;

        Variable *var1 = operands->top();
        operands->pop();
        Variable *var2 = operands->top();
        operands->pop();

        Variable *res = new Variable("I");
        *((int *) res->variable->intValue) = *((int *) var1->variable->intValue) | *((int *) var2->variable->intValue);
        operands->push(res);
    };
    OPCODE_CB(0x81){
        // LOR
        (*pc)++;

        Variable *var1 = operands->top();
        operands->pop();
        long long s1 = *((long long*)var1->variable->longValue);
        Variable *var2 = operands->top();
        operands->pop();
        long long s2 = *((long long*)var2->variable->longValue);

        Variable *res = new Variable("J");
        long long _or = s2 | s1;
        *((long long*) res->variable->longValue) = _or;
        operands->push(res);
    };
    OPCODE_CB(0x82){
        // IXOR
        (*pc)++;

        Variable *var1 = operands->top();
        operands->pop();
        Variable *var2 = operands->top();
        operands->pop();

        Variable *res = new Variable("I");
        *((int *) res->variable->intValue) = *((int *) var1->variable->intValue) ^ *((int *) var2->variable->intValue);
        operands->push(res);
    };
    OPCODE_CB(0x83){
        // LXOR
        (*pc)++;

        Variable *var1 = operands->top();
        operands->pop();
        long long s1 = *((long long*)var1->variable->longValue);
        Variable *var2 = operands->top();
        operands->pop();
        long long s2 = *((long long*)var2->variable->longValue);

        Variable *res = new Variable("J");
        long long _xor = s2 ^ s1;
        *((long long*) res->variable->longValue) = _xor;
        operands->push(res);
    };
    OPCODE_CB(0x84){
        // IINC
        (*pc)++;

        uint8_t idx = code[(*pc)++];
        int8_t iinc = code[(*pc)++];

        int32_t res = ((iinc & 0x80) == 0) ? iinc : 0x00 | iinc;
        (*localVariables)[idx]->variable->intValue += res;
    };
    OPCODE_CB(0x85){
        // I2L
        (*pc)++;

        Variable *var = operands->top();
        Variable *ans = new Variable("J");

        operands->pop();
        *((long *) ans->variable->longValue) = (long)(*((int *) var->variable->intValue));
        operands->push(ans);
    };
    OPCODE_CB(0x86){
        // I2F
        (*pc)++;

        Variable *var = operands->top();
        Variable *ans = new Variable("F");

        operands->pop();
        *((float *) ans->variable->floatValue) = (float)(*((int *) var->variable->intValue));
        operands->push(ans);
    };
    OPCODE_CB(0x87){
        // I2D
        (*pc)++;

        Variable *var = operands->top();
        Variable *ans = new Variable("D");

        operands->pop();
        *((double *) ans->variable->doubleValue) = (double)(*((int *) var->variable->intValue));
        operands->push(ans);
    };
    OPCODE_CB(0x88){
        // L2I
        (*pc)++;

        Variable *var = operands->top();
        Variable *ans = new Variable("I");

        operands->pop();
        *((int *) ans->variable->intValue) = (int)(*((long *) var->variable->longValue));
        operands->push(ans);
    };
    OPCODE_CB(0x89){
        // L2F
        (*pc)++;

        Variable *var = operands->top();
        Variable *ans = new Variable("F");

        operands->pop();
        *((float *) ans->variable->floatValue) = (float)(*((long *) var->variable->longValue));
        operands->push(ans);
    };
    OPCODE_CB(0x8A){
        // L2D
        (*pc)++;

        Variable *var = operands->top();
        Variable *ans = new Variable("D");

        operands->pop();
        *((double *) ans->variable->doubleValue) = (double)(*((long *) var->variable->longValue));
        operands->push(ans);
    };
    OPCODE_CB(0x8B){
        // F2I
        (*pc)++;

        Variable *var = operands->top();
        Variable *ans = new Variable("I");

        operands->pop();
        *((int *) ans->variable->intValue) = (int)(*((float *) var->variable->floatValue));
        operands->push(ans);
    };
    OPCODE_CB(0x8C){
        // F2L
        (*pc)++;

        Variable *var = operands->top();
        Variable *ans = new Variable("J");

        operands->pop();
        *((long *) ans->variable->longValue) = (long)(*((float *) var->variable->floatValue));
        operands->push(ans);
    };
    OPCODE_CB(0x8D){
        // F2D
        (*pc)++;

        Variable *var = operands->top();
        Variable *ans = new Variable("D");

        operands->pop();
        *((double *) ans->variable->doubleValue) = (double)(*((float *) var->variable->floatValue));
        operands->push(ans);
    };
    OPCODE_CB(0x8E){
        // D2I
        (*pc)++;

        Variable *var = operands->top();
        Variable *ans = new Variable("I");

        operands->pop();
        *((int *) ans->variable->intValue) = (int)(*((double *) var->variable->doubleValue));
        operands->push(ans);
    };
    OPCODE_CB(0x8F){
        // D2L
        (*pc)++;

        Variable *var = operands->top();
        Variable *ans = new Variable("J");

        operands->pop();
        *((long *) ans->variable->longValue) = (long)(*((double *) var->variable->doubleValue));
        operands->push(ans);
    };
    OPCODE_CB(0x90){
        // D2F
        (*pc)++;

        Variable *var = operands->top();
        Variable *ans = new Variable("F");

        operands->pop();
        *((float *) ans->variable->floatValue) = (float)(*((double *) var->variable->doubleValue));
        operands->push(ans);
    };
    OPCODE_CB(0x91){
        // I2B
        (*pc)++;

        Variable *var = operands->top();
        Variable *ans = new Variable("B");

        operands->pop();
        *((unsigned char *) ans->variable->byteValue) = (unsigned char)(*((int *) var->variable->intValue));
        operands->push(ans);
    };
    OPCODE_CB(0x92){
        // I2C
        (*pc)++;

        Variable *var = operands->top();
        Variable *ans = new Variable("C");

        operands->pop();
        *((char *) ans->variable->charValue) = (char)(*((int *) var->variable->intValue));
        operands->push(ans);
    };
    OPCODE_CB(0x93){
        // I2S
        (*pc)++;

        Variable *var = operands->top();
        Variable *ans = new Variable("S");

        operands->pop();
        *((short *) ans->variable->shortValue) = (short)(*((int *) var->variable->intValue));
        operands->push(ans);
    };
    OPCODE_CB(0x94){
        // LCMP
        (*pc)++;

        Variable *lv2 = operands->top();
        operands->pop();
        Variable *lv1 = operands->top();
        operands->pop();

        Variable *ans = new Variable("I");

        if (*lv1->variable->longValue > *lv2->variable->longValue) {
            *ans->variable->intValue = 1;
        }
        else if (*lv1->variable->longValue < *lv2->variable->longValue) {
            *ans->variable->intValue = -1;
        }
        else {
            *ans->variable->intValue = 0;
        }

        operands->push(ans);
    };
    OPCODE_CB(0x95){
        // FCMPL
        (*pc)++;

        Variable *fv2 = operands->top();
        operands->pop();
        Variable *fv1 = operands->top();
        operands->pop();

        Variable *ans = new Variable("I");

        if (*((float *) fv1->variable->floatValue) > *((float *) fv2->variable->floatValue)) {
            *ans->variable->intValue = 1;
        }
        else if (*((float *) fv1->variable->floatValue) < *((float *) fv2->variable->floatValue)) {
            *ans->variable->intValue = -1;
        }
        else if (*((float *) fv1->variable->floatValue) == *((float *) fv2->variable->floatValue)) {
            *ans->variable->intValue = 0;
        }
        else {
            *ans->variable->intValue = -1;
        }

        operands->push(ans);
    };
    OPCODE_CB(0x96){
        // FCMPG
        (*pc)++;

        Variable *fv2 = operands->top();
        operands->pop();
        Variable *fv1 = operands->top();
        operands->pop();

        Variable *ans = new Variable("I");

        if (*((float *) fv1->variable->floatValue) > *((float *) fv2->variable->floatValue)) {
            *ans->variable->intValue = 1;
        }
        else if (*((float *) fv1->variable->floatValue) < *((float *) fv2->variable->floatValue)) {
            *ans->variable->intValue = -1;
        }
        else if (*((float *) fv1->variable->floatValue) == *((float *) fv2->variable->floatValue)) {
            *ans->variable->intValue = 0;
        }
        else {
            *ans->variable->intValue = 1;
        }

        operands->push(ans);
    };
    OPCODE_CB(0x97){
        // DCMPL
        (*pc)++;

        Variable *dv2 = operands->top();
        operands->pop();
        Variable *dv1 = operands->top();
        operands->pop();

        Variable *ans = new Variable("I");

        if (*((double *) dv1->variable->doubleValue) > *((double *) dv2->variable->doubleValue)) {
            *ans->variable->intValue = 1;
        }
        else if (*((double *) dv1->variable->doubleValue) < *((double *) dv2->variable->doubleValue)) {
            *ans->variable->intValue = -1;
        }
        else if (*((double *) dv1->variable->doubleValue) == *((double *) dv2->variable->doubleValue)) {
            *ans->variable->intValue = 0;
        }
        // else {
        //     *ans->variable->intValue = -1;
        // }

        operands->push(ans);
    };
    OPCODE_CB(0x98){
        // DCMPG
        (*pc)++;

        Variable *dv2 = operands->top();
        operands->pop();
        Variable *dv1 = operands->top();
        operands->pop();

        Variable *ans = new Variable("I");

        if (*((double *) dv1->variable->doubleValue) > *((double *) dv2->variable->doubleValue)) {
            *ans->variable->intValue = 1;
        }
        else if (*((double *) dv1->variable->doubleValue) < *((double *) dv2->variable->doubleValue)) {
            *ans->variable->intValue = -1;
        }
        else if (*((double *) dv1->variable->doubleValue) == *((double *) dv2->variable->doubleValue)) {
            *ans->variable->intValue = 0;
        }
        else {
            *ans->variable->intValue = 1;
        }

        operands->push(ans);
    };
    OPCODE_CB(0x99){
        // IFEQ
        Variable* value = operands->top();
        if (value->tag != Variable::type::_int){
            throw std::runtime_error("IFEQ operand must be an integer");
        }
        operands->pop();
        if (*value->variable->intValue != 0){
            PCINC(3);
            return;
        }

        s2 signed_offset = ((u2)GETIMM(1) << 8 | GETIMM(2));
        PCINC(signed_offset);
    };
    OPCODE_CB(0x9A){
        // IFNE
        short offset = 0;
        Variable *var = operands->top();
        operands->pop();

        if (*var->variable->intValue != 0) {
            offset = *(code + (*pc + 1));
            offset <<= 8;
            offset |= *(code + (*pc + 2));
            (*pc) += offset;
        }
        else {
            (*pc) += 3;
        }
    };
    OPCODE_CB(0x9B){
        // IFLT
        short offset = 0;
        Variable *var = operands->top();
        operands->pop();

        if (*((int *) var->variable->intValue) < 0) {
            offset = *(code + (*pc + 1));
            offset <<= 8;
            offset |= *(code + (*pc + 2));
            (*pc) += offset;
        }
        else {
            (*pc) += 3;
        }
    };
    OPCODE_CB(0x9C){
        // IFGE
        short offset = 0;
        Variable *var = operands->top();
        operands->pop();

        if (*((int *) var->variable->intValue) >= 0) {
            offset = *(code + (*pc + 1));
            offset <<= 8;
            offset |= *(code + (*pc + 2));
            (*pc) += offset;
        }
        else {
            (*pc) += 3;
        }
    };
    OPCODE_CB(0x9D){
        // IFGT
        short offset = 0;
        Variable *var = operands->top();
        operands->pop();

        if (*((int *) var->variable->intValue) > 0) {
            offset = *(code + (*pc + 1));
            offset <<= 8;
            offset |= *(code + (*pc + 2));
            (*pc) += offset;
        }
        else {
            (*pc) += 3;
        }
    };
    OPCODE_CB(0x9E){
        // IFLE
        short offset = 0;
        Variable *var = operands->top();
        operands->pop();

        if (*((int *) var->variable->intValue) <= 0) {
            offset = *(code + (*pc + 1));
            offset <<= 8;
            offset |= *(code + (*pc + 2));
            (*pc) += offset;
        }
        else {
            (*pc) += 3;
        }
    };
    OPCODE_CB(0x9F){
        // IF_ICMPEQ
        short offset = 0;
        Variable *iv2 = operands->top();
        operands->pop();
        Variable *iv1 = operands->top();
        operands->pop();

        if (*iv1->variable->intValue == *iv2->variable->intValue) {
            offset = *(code + (*pc + 1));
            offset <<= 8;
            offset |= *(code + (*pc + 2));
            (*pc) += offset;
        }
        else {
            (*pc) += 3;
        }
    };
    OPCODE_CB(0xA0){
        // IF_ICMPNE
        short offset = 0;
        Variable *iv2 = operands->top();
        operands->pop();
        Variable *iv1 = operands->top();
        operands->pop();

        if (*iv1->variable->intValue != *iv2->variable->intValue) {
            offset = *(code + (*pc + 1));
            offset <<= 8;
            offset |= *(code + (*pc + 2));
            (*pc) += offset;
        }
        else {
            (*pc) += 3;
        }
    };
    OPCODE_CB(0xA1){
        // IF_ICMPLT
        short offset = 0;
        Variable *iv2 = operands->top();
        operands->pop();
        Variable *iv1 = operands->top();
        operands->pop();

        if (*iv1->variable->intValue < *iv2->variable->intValue) {
            offset = *(code + (*pc + 1));
            offset <<= 8;
            offset |= *(code + (*pc + 2));
            (*pc) += offset;
        }
        else {
            (*pc) += 3;
        }
    };
    OPCODE_CB(0xA2){
        // IF_ICMPGE
        short offset = 0;
        Variable *iv2 = operands->top();
        operands->pop();
        Variable *iv1 = operands->top();
        operands->pop();

        if (*iv1->variable->intValue >= *iv2->variable->intValue) {
            offset = *(code + (*pc + 1));
            offset <<= 8;
            offset |= *(code + (*pc + 2));
            (*pc) += offset;
        }
        else {
            (*pc) += 3;
        }
    };
    OPCODE_CB(0xA3){
        // IF_ICMPGT
        short offset = 0;
        Variable *iv2 = operands->top();
        operands->pop();
        Variable *iv1 = operands->top();
        operands->pop();

        if (*iv1->variable->intValue > *iv2->variable->intValue) {
            offset = *(code + (*pc + 1));
            offset <<= 8;
            offset |= *(code + (*pc + 2));
            (*pc) += offset;
        }
        else {
            (*pc) += 3;
        }
    };
    OPCODE_CB(0xA4){
        // IF_ICMPLE
        short offset = 0;
        Variable *iv2 = operands->top();
        operands->pop();
        Variable *iv1 = operands->top();
        operands->pop();

        if (*iv1->variable->intValue <= *iv2->variable->intValue) {
            offset = *(code + (*pc + 1));
            offset <<= 8;
            offset |= *(code + (*pc + 2));
            (*pc) += offset;
        }
        else {
            (*pc) += 3;
        }
    };
    OPCODE_CB(0xA5){
        // IF_ACMPEQ
        Variable *av2 = operands->top();
        operands->pop();
        Variable *av1 = operands->top();
        operands->pop();

        if (av1->object == av2->object) {
            (*pc) += ((*(pc + 1)) << 8) + (*(pc + 2));
        }
    };
    OPCODE_CB(0xA6){
        // IF_ACMPNE
        Variable *av2 = operands->top();
        operands->pop();
        Variable *av1 = operands->top();
        operands->pop();

        if (av1->object != av2->object) {
            (*pc) += ((*(pc + 1)) << 8) + (*(pc + 2));
        }
        else {
            (*pc) += 3;
        }
    };
    OPCODE_CB(0xA7){
        // GOTO
        short offset = *(code + (*pc + 1));
        offset <<= 8;
        offset |= *(code + (*pc + 2));
        (*pc) += offset;
    };
    OPCODE_CB(0xA8){
        // JSR
        Variable *var = new Variable("RA");
        *var->returnAddress = (*pc) + 3;
        operands->push(var);

        short offset = *(code + (*pc + 1));
        offset <<= 8;
        offset |= *(code + (*pc + 2));
        (*pc) += offset;
    };
    OPCODE_CB(0xA9){
        // RET
        (*pc) = *(localVariables->at(*(code + ((*pc) + 1)))->returnAddress);
    };
    OPCODE_CB(0xAA){
        // TABLESWITCH
        uint32_t st = *pc;
        uint32_t h_byte = 0;
        uint32_t l_byte = 0;
        uint32_t def_byte = 0;
        uint32_t *jump_table;

        uint32_t idx = *operands->top()->variable->intValue;
        operands->pop();

        (*pc)++;
        uint32_t aux = (*pc) % 4;
        (*pc) += (aux == 0) ? 0 : (4 - aux);

        for (int i = 0; i < 4; i++) {
            def_byte = (def_byte << 8) + code[(*pc)++];
        }

        for (int i = 0; i < 4; i++) {
            l_byte = (l_byte << 8) + code[(*pc)++];
        }

        for (int i = 0; i < 4; i++) {
            h_byte = (h_byte << 8) + code[(*pc)++];
        }

        aux = h_byte - l_byte + 1;
        jump_table = (uint32_t *) calloc (aux, sizeof(uint32_t));

        if (!jump_table) {
            throw "Unable to allocate memory on 0xAA \"Frame.cpp\" instruction.\n";
        }

        for (int i = 0; i < (int) aux; i++) {
            for (int j = 0; j < 4; j++) {
                jump_table[i] = (jump_table[i] << 8) + code[(*pc)++];
            }
        }

        if (idx < l_byte || idx > h_byte) {
            *pc = st + def_byte;
        }
        else {
            *pc = st + jump_table[idx - l_byte];
        }
    };
    OPCODE_CB(0xAB){
        // LOOKUPSWITCH
        uint32_t st = *pc;
        uint32_t npairs = 0;
        uint32_t def_byte = 0;
        uint32_t *offsets;
        int32_t *match;

        int32_t key = *operands->top()->variable->intValue;
        operands->pop();

        (*pc)++;
        uint32_t aux = (*pc) % 4;
        (*pc) += (aux == 0) ? 0 : (4 - aux);

        for (int i = 0; i < 4; i++) {
            def_byte = (def_byte << 8) + code[(*pc)++];
        }

        for (int i = 0; i < 4; i++) {
            npairs = (npairs << 8) + code[(*pc)++];
        }

        match = (int32_t *) calloc (npairs, sizeof(int32_t));
        offsets = (uint32_t *) calloc (npairs, sizeof(uint32_t));

        if (!match || !offsets) {
            throw "Unable to allocate memory on 0xAB \"Frame.cpp\" instruction.\n";
        }

        for (int i = 0; i < (int) npairs; i++) {
            for (int j = 0; j < 4; j++) {
                match[i] = (match[i] << 8) + code[(*pc)++];
            }

            for (int j = 0; j < 4; j++) {
                offsets[i] = (offsets[i] << 8) + code[(*pc)++];
            }
        }

        bool flag = true;
        for (int i = 0; i < (int) npairs; i++) {
            if (key == match[i]) {
                *pc = st + offsets[i];
                flag = false;
                break;
            }
        }

        if (flag) {
            *pc = st + def_byte;
        }
    };
    OPCODE_CB(0xAC){
        // IRETURN
        (*pc)++;
        Variable *var = operands->top();
        operands->pop();
        Heap::getInstance()->popFrame();
        Frame *top = Heap::getInstance()->frameTop();
        operands = top->getStack();
        Heap::getInstance()->frameTop()->pushOpStack(operands, var);
    };
    OPCODE_CB(0xAD){
        // LRETURN
        (*pc)++;
        Variable *var = operands->top();
        operands->pop();
        Heap::getInstance()->popFrame();
        Frame *top = Heap::getInstance()->frameTop();
        operands = top->getStack();
        Heap::getInstance()->frameTop()->pushOpStack(operands, var);
    };
    OPCODE_CB(0xAE){
        // FRETURN
        (*pc)++;
        Variable *var = operands->top();
        operands->pop();
        Heap::getInstance()->popFrame();
        Frame *top = Heap::getInstance()->frameTop();
        operands = top->getStack();
        Heap::getInstance()->frameTop()->pushOpStack(operands, var);
    };
    OPCODE_CB(0xAF){
        // DRETURN
        (*pc)++;
        Variable *var = operands->top();
        Heap::getInstance()->popFrame();
        Frame *top = Heap::getInstance()->frameTop();
        operands = top->getStack();
        Heap::getInstance()->frameTop()->pushOpStack(operands, var);
    };
    OPCODE_CB(0xB0){
        // ARETURN
        (*pc)++;
        Variable *var = operands->top();
        Heap::getInstance()->popFrame();
        Frame *top = Heap::getInstance()->frameTop();
        operands = top->getStack();
        Heap::getInstance()->frameTop()->pushOpStack(operands, var);
    };
    OPCODE_CB(0xB1){
        // RETURN
        PCINC(1);
        Heap::getInstance()->popFrame();
    };
    OPCODE_CB(0xB2){
        // GETSTATIC
        (*pc)++;

        uint16_t aux = code[(*pc)++];
        uint16_t idx = (aux << 8) + code[(*pc)++];

        aux = cp->getCpInfoElement(idx).constant_element.c3->class_index;
        uint16_t className = cp->getCpInfoElement(aux).constant_element.c1->name_index;

        aux = cp->getCpInfoElement(idx).constant_element.c3->name_and_type_index;
        uint16_t fieldName = cp->getCpInfoElement(aux).constant_element.c10->name_index;

        std::string s((char *)cp->getCpInfoElement(className).constant_element.c11->bytes, (size_t) cp->getCpInfoElement(className).constant_element.c11->length);
        if (s != "java/lang/System") {
            Heap::getInstance()->getClass(s);
            std::string s1((char *)cp->getCpInfoElement(className).constant_element.c11->bytes, (size_t) cp->getCpInfoElement(className).constant_element.c11->length);
            std::string s2((char *)cp->getCpInfoElement(fieldName).constant_element.c11->bytes, (size_t) cp->getCpInfoElement(fieldName).constant_element.c11->length);
            Variable *value = Heap::getInstance()->getStaticInfo(s1, s2);
            operands->push(value);
        }
    };
    OPCODE_CB(0xB3){
        // PUTSTATIC
        (*pc)++;

        uint16_t aux = code[(*pc)++];
        uint16_t idx = (aux << 8) + code[(*pc)++];

        aux = cp->getCpInfoElement(idx).constant_element.c3->class_index;
        uint16_t className = cp->getCpInfoElement(aux).constant_element.c1->name_index;

        aux = cp->getCpInfoElement(idx).constant_element.c3->name_and_type_index;
        uint16_t fieldName = cp->getCpInfoElement(aux).constant_element.c10->name_index;

        std::string s1((char *)cp->getCpInfoElement(className).constant_element.c11->bytes, (size_t) cp->getCpInfoElement(className).constant_element.c11->length);
        std::string s2((char *)cp->getCpInfoElement(fieldName).constant_element.c11->bytes, (size_t) cp->getCpInfoElement(fieldName).constant_element.c11->length);
        Heap::getInstance()->getClass(s1);
        Variable *value = Heap::getInstance()->getStaticInfo(s1, s2);

        switch (value->tag) {
            case Variable::type::_byte:
                *value->variable->byteValue = *operands->top()->variable->byteValue;
                operands->pop();
                break;
            case Variable::type::_bool:
                *value->variable->booleanValue = *operands->top()->variable->booleanValue;
                operands->pop();
                break;
            case Variable::type::_char:
                *value->variable->charValue = *operands->top()->variable->charValue;
                operands->pop();
                break;
            case Variable::type::_short:
                *value->variable->shortValue = *operands->top()->variable->shortValue;
                operands->pop();
                break;
            case Variable::type::_int:
                *value->variable->intValue = *operands->top()->variable->intValue;
                operands->pop();
                break;
            case Variable::type::_float:
                *value->variable->floatValue = *operands->top()->variable->floatValue;
                operands->pop();
                break;
            case Variable::type::_long:
                *value->variable->longValue = *operands->top()->variable->longValue;
                operands->pop();
                break;
            case Variable::type::_double:
                *value->variable->doubleValue = *operands->top()->variable->doubleValue;
                operands->pop();
                break;
            case Variable::type::_classInstance:
                *value->object = *operands->top()->object;
                operands->pop();
                break;
            case Variable::type::_array:
                *value->array = *operands->top()->array;
                operands->pop();
                break;
            case Variable::type::_string:
                *value->string = *operands->top()->string;
                operands->pop();
                break;
            case Variable::type::_returnAddress:
                *value->returnAddress = *operands->top()->returnAddress;
                operands->pop();
                break;
            default:
                std::cout << "Check putstatic instruction, maybe something bad happened.\n";
        }
    };
    OPCODE_CB(0xB4){
        // GETFIELD
        // throw "Instruction 0xB4 not implemented yet.\n";
        (*pc)++;
        if(operands->top()->tag == Variable::type::_classInstance){
            Variable *objectref = operands->top();
            operands->pop();

            u2 indexbyte1 = code[(*pc)++];
            u2 indexbyte2 = code[(*pc)++];
            u4 index = (indexbyte1 << 8) + (indexbyte2);
            
            //@@ Cp_info *runtime = &(cp->getCpInfoElement(index-1));
            
            // u2 className  = runtime->info.fieldrefInfo.class_index;
            //@@ u2 fieldName  = cp[runtime.constant_element.c3->name_and_type_index - 1].info.nameAndTypeInfo.name_index;
            u2 fieldName  = cp->getCpInfoElement(cp->getCpInfoElement(index).constant_element.c3->name_and_type_index).constant_element.c10->name_index;
            // u2 fieldType  = cp[runtime->info.fieldrefInfo.name_and_type_index - 1].info.nameAndTypeInfo.descriptor_index;

            std::string key = jClassInstance->javaClass->getUTF8(fieldName);

            Variable *field = objectref->object->fieldVariables->at(key);
            operands->push(field);
        } else
            throw "NullPointerException";
    };
    OPCODE_CB(0xB5){
        // PUTFIELD
        // throw "Instruction 0xB5 not implemented yet.\n";
        (*pc)++;
        
        u2 indexbyte1 = code[(*pc)++];
        u2 indexbyte2 = code[(*pc)++];
        u4 index = (indexbyte1 << 8) + (indexbyte2);

        //@@ cp_info* fieldRef = &cp[index - 1];
        // u2 className = cp[fieldRef->info.fieldrefInfo.class_index - 1].info.classInfo.name_index;
        u2 fieldName = cp->getCpInfoElement(cp->getCpInfoElement(index).constant_element.c3->name_and_type_index).constant_element.c10->name_index;
        u2 fieldType = cp->getCpInfoElement(cp->getCpInfoElement(index).constant_element.c3->name_and_type_index).constant_element.c10->descriptor_index;

        Variable *field = new Variable(jClassInstance->javaClass->getUTF8(fieldType));
        
        Variable *value = operands->top();
        operands->pop();
        // Variable *objectref = operands->top();
        // operands->pop();
        
        std::string key;
        key = jClassInstance->javaClass->getUTF8(fieldName);
        field = jClassInstance->fieldVariables->at(key);
        switch(field->tag){
            case Variable::type::_int:
            *field->variable->intValue = *value->variable->intValue;
            break;
            case Variable::type::_float:
            *field->variable->floatValue = *value->variable->floatValue;
            break;
            case Variable::type::_short:
            *field->variable->shortValue = *value->variable->shortValue;
            break;
            case Variable::type::_bool:
            *field->variable->booleanValue = *value->variable->booleanValue;
            break;
            case Variable::type::_char:
            *field->variable->charValue = *value->variable->charValue;
            break;
            case Variable::type::_classInstance:
            *field->object = *value->object;
            break;
            case Variable::type::_array:
            *field->array = *value->array;
            break;
            case Variable::type::_double:
            *field->variable->doubleValue = *value->variable->doubleValue;
            break;
            case Variable::type::_long:
            *field->variable->longValue = *value->variable->longValue;
            break;
            default:
                throw "Invalid Field Type\n";
        }

        // std::cout << "what" << std::endl;
    };
    OPCODE_CB(0xB6){
        // INVOKEVIRTUAL
        double dStream;
        float  fStream;
        (*pc)++;

        uint16_t aux = code[(*pc)++];
        uint16_t idx = (aux << 8) + code[(*pc)++];

        //@@ cp_info *ref2meth = &cp[idx - 1];
        uint16_t class_name_idx = cp->getCpInfoElement(cp->getCpInfoElement(idx).constant_element.c2->class_index).constant_element.c1->name_index;
        std::string cl_name((char *) cp->getCpInfoElement(class_name_idx).constant_element.c11->bytes, (size_t) cp->getCpInfoElement(class_name_idx).constant_element.c11->length);

        uint16_t name_type_idx = cp->getCpInfoElement(idx).constant_element.c2->name_and_type_index;
        //@@ cp_info *name_type = &cp[name_type_idx - 1];

        std::string meth_name((char *) cp->getCpInfoElement(cp->getCpInfoElement(name_type_idx).constant_element.c10->name_index).constant_element.c11->bytes, (size_t) cp->getCpInfoElement(cp->getCpInfoElement(name_type_idx).constant_element.c10->name_index).constant_element.c11->length);
        std::string meth_desc((char *) cp->getCpInfoElement(cp->getCpInfoElement(name_type_idx).constant_element.c10->descriptor_index).constant_element.c11->bytes, (size_t) cp->getCpInfoElement(cp->getCpInfoElement(name_type_idx).constant_element.c10->descriptor_index).constant_element.c11->length);

        if (cl_name.find("java/") == 0) {
            if (cl_name == "java/io/PrintStream" && (meth_name == "print" || meth_name == "println")) {
                if (meth_desc != "()V") {
                    Variable *stream = operands->top();
                    operands->pop();
                    switch (stream->tag) {
                        case Variable::type::_byte:
                            std::cout << *((int8_t *)stream->variable->byteValue);
                            break;
                        case Variable::type::_bool:
                            std::cout << *((bool*)stream->variable->booleanValue);
                            break;
                        case Variable::type::_char:
                            std::cout << *((char*)stream->variable->charValue);
                            break;
                        case Variable::type::_short:
                            std::cout << *((short*)stream->variable->shortValue);
                            break;
                        case Variable::type::_int:
                            std::cout << *((int32_t*)stream->variable->intValue);
                            break;
                        case Variable::type::_float:
                            fStream = *((float*)stream->variable->floatValue);
                            printf("%.6f", fStream);
                            break;
                        case Variable::type::_long:
                            std::cout << *((int64_t*)stream->variable->longValue);
                            break;
                        case Variable::type::_double:
                            dStream = *((double*)stream->variable->doubleValue);
                            printf("%.12lf", dStream);
                            break;
                        case Variable::type::_classInstance:
                            std::cout << stream->object->javaClass;
                            break;
                        case Variable::type::_array:
                            std::cout << stream->array->array;
                            break;
                        case Variable::type::_string:
                            std::cout << *stream->string;
                            break;
                        default: break;
                    }
                }
                if (meth_name == "println") {
                    std::cout << "\n";
                }
            }
            else if (cl_name == "java/lang/String" && meth_name == "equals") {
                Variable *aux1 = operands->top();
                operands->pop();
                Variable *aux2 = operands->top();
                operands->pop();

                Variable *var = new Variable("Z");
                *var->variable->booleanValue = (aux1->string == aux2->string) ? true : false;
                operands->push(var);
            }
            else if (cl_name == "java/lang/String" && meth_name == "length") {
                Variable *aux1 = operands->top();
                operands->pop();

                Variable *var = new Variable("I");
                *var->variable->intValue = (int32_t) aux1->string->size();
                operands->push(var);
            }
            else if (cl_name == "java/lang/StringBuilder" && meth_name == "append") {
                Variable *aux1 = operands->top();
                operands->pop();
                Variable *aux2 = operands->top();
                operands->pop();

                std::stringstream ap;
                switch (aux1->tag) {
                    case Variable::type::_byte:
                        ap << std::to_string(*((int8_t *)aux1->variable->byteValue));
                        break;
                    case Variable::type::_bool:
                        ap << std::to_string(*((bool*)aux1->variable->booleanValue));
                        break;
                    case Variable::type::_char:
                        ap << std::to_string(*((char*)aux1->variable->charValue));
                        break;
                    case Variable::type::_short:
                        ap << std::to_string(*((int16_t*)aux1->variable->shortValue));
                        break;
                    case Variable::type::_int:
                        ap << std::to_string(*((int*)aux1->variable->intValue));
                        break;
                    case Variable::type::_float:
                        ap << std::to_string(*((float*)aux1->variable->floatValue));
                        break;
                    case Variable::type::_long:
                        ap << std::to_string(*((int64_t*)aux1->variable->longValue));
                        break;
                    case Variable::type::_double:
                        ap << std::to_string(*((double*)aux1->variable->doubleValue));
                        break;
                    case Variable::type::_classInstance:
                        ap << aux1->object;
                        break;
                    case Variable::type::_array:
                        ap << aux1->array;
                        break;
                    case Variable::type::_string:
                        ap << *aux1->string;
                        break;
                    default: break;
                }

                aux2->string->append(ap.str());
                operands->push(aux2);
            }
            else if (cl_name == "java/lang/StringBuilder") {
                return;
            }
            else {
                std::cout << "method < " << meth_name << " > not implemented yet.\n";
                exit(1);
            }
        }
        else {
            uint16_t i = 1;
            uint16_t n_args = 0;

            while (meth_desc[i] != ')') {
                char c = meth_desc[i];
                n_args++;
                if (c == 'L') {
                    while (meth_desc[++i] != ';');
                }
                else if (c == '[') {
                    while (meth_desc[++i] == '[');
                    if (meth_desc[i] == 'L') {
                        while (meth_desc[++i] != ';');
                    }
                }
                i++;
            }

            std::vector < Variable * > args;
            for (uint16_t i = 0; i < n_args; i++) {
                args.insert(args.begin(), operands->top());
                operands->pop();
                if (args[0]->tag == Variable::type::_double || args[0]->tag == Variable::type::_long) {
                    args.insert(args.begin() + 1, new Variable());
                }
            }

            Variable *val = operands->top();
            operands->pop();
            args.insert(args.begin(), val);

            Frame *newFrame = new Frame(val->object->javaClass, cp, name_type_idx, val->object, &args);
            Heap::getInstance()->pushFrame(newFrame);
        }
    };
    OPCODE_CB(0xB7){
        // INVOKESPECIAL
        u2 methodIndex = code[++(*pc)];
        methodIndex = (methodIndex<<8) | code[++(*pc)];
        (*pc)++;

        //@@ cp_info* methodRef = &cp[methodIndex - 1];

        //@@ cp_info* classInfo = cp->getCpInfoElement(cp->getCpInfoElement(methodIndex).constant_element.c2->class_index - 1);
        u2 classNameIndex  = cp->getCpInfoElement(cp->getCpInfoElement(methodIndex).constant_element.c2->class_index).constant_element.c1->name_index;
        std::string className(jClassInstance->javaClass->getUTF8(classNameIndex));

        u2 nameAndTypeIndex = cp->getCpInfoElement(methodIndex).constant_element.c2->name_and_type_index;
        //@@ cp_info* nameAndType = &cp[nameAndTypeIndex - 1];

        std::string methodName = jClassInstance->javaClass->getUTF8(cp->getCpInfoElement(nameAndTypeIndex).constant_element.c10->name_index);
        std::string methodType = jClassInstance->javaClass->getUTF8(cp->getCpInfoElement(nameAndTypeIndex).constant_element.c10->descriptor_index);

        // Caso de Object<init>, String<init>, StringBuilder<init>
        if (((className == "java/lang/Object" || className == "java/lang/String") && methodName == "<init>") ||
            (className == "java/lang/StringBuilder" && methodName == "<init>")) {
            if (className == "java/lang/String" || className == "java/lang/StringBuilder") {
                operands->pop();
            }
            else if(methodName == "<init>"){
                Heap::getInstance()->addInstanceFields(localVariables->at(0)->object);
            }
            return;
        }
        //Caso forem outras classes do java nao implementadas aqui
        if (strstr(className.c_str(), (char*)"java/") != NULL){
            std::cout << className << " Nao implementada!\n";
            exit(1);
        }
        else {
            u2 nargs = 0; // numero de argumentos contidos na pilha de operandos
            u2 index = 1;
            while (methodType[index] != ')') {
                char baseType = methodType[index];
                //Argumento do tipo objeto
                if (baseType == 'L') {
                    nargs++;
                    while (methodType[++index] != ';');
                }
                //Argumento do tipo array
                else if (baseType == '[') {
                    nargs++;
                    while (methodType[++index] == '[');
                    if (methodType[index] == 'L')
                        while (methodType[++index] != ';');
                }
                else {
                    nargs++;
                }
                index++;
            }

            std::vector<Variable*> args;
            for (int i = 0; i < nargs; i++) {
                Variable* value = operands->top();
                operands->pop();
                args.insert(args.begin(), value);
                if (value->tag == Variable::type::_double || value->tag == Variable::type::_long)
                    args.insert(args.begin() +1, new Variable());
            }

            //Adicionar objectref pro inicio dos argumentos
            Variable* objectValue = operands->top();
            operands->pop();
            args.insert(args.begin(), objectValue);

            // JavaClass *newJClass = objectValue->object->javaClass;
            Leitor *newJClass = objectValue->object->javaClass;
            u2 aux;
            for(aux = 0; aux < newJClass->get(METHODS_COUNT); aux++){
                std::string name = newJClass->getUTF8(newJClass->getMethods()->methods[aux]->name_index);
                std::string desc = newJClass->getUTF8(newJClass->getMethods()->methods[aux]->descriptor_index);
                if(name.compare(methodName) == 0 && desc.compare(methodType) == 0)
                    break;
            }
            Frame* nextFrame = new Frame(newJClass, newJClass->getConstantPool(), aux, objectValue->object, &args);
            Heap::getInstance()->pushFrame(nextFrame);
        }
    };
    OPCODE_CB(0xB8){
        // INVOKESTATIC
        (*pc)++;

        uint16_t aux = code[(*pc)++];
        uint16_t idx = (aux << 8) + code[(*pc)++];

        //@@ cp_info *ref2meth = &cp[idx - 1];

        uint16_t class_name_idx = cp->getCpInfoElement(cp->getCpInfoElement(idx).constant_element.c2->class_index).constant_element.c1->name_index;
        std::string cl_name((char *) cp->getCpInfoElement(class_name_idx).constant_element.c11->bytes, (size_t) cp->getCpInfoElement(class_name_idx).constant_element.c11->length);

        uint16_t name_type_idx = cp->getCpInfoElement(idx).constant_element.c2->name_and_type_index;
        //@@ cp_info *name_type = &cp[name_type_idx - 1];

        std::string meth_name((char *) cp->getCpInfoElement(cp->getCpInfoElement(name_type_idx).constant_element.c10->name_index).constant_element.c11->bytes, (size_t) cp->getCpInfoElement(cp->getCpInfoElement(name_type_idx).constant_element.c10->name_index).constant_element.c11->length);
        std::string meth_desc((char *) cp->getCpInfoElement(cp->getCpInfoElement(name_type_idx).constant_element.c10->descriptor_index).constant_element.c11->bytes, (size_t) cp->getCpInfoElement(cp->getCpInfoElement(name_type_idx).constant_element.c10->descriptor_index).constant_element.c11->length);

        if (cl_name == "java/lang/Object" && meth_name == "registerNatives") {
            // codigo nativo
            return;
        }

        if (cl_name.find("java/") == std::string::npos) {
            uint16_t i = 1;
            uint16_t n_args = 0;

            while (meth_desc[i] != ')') {
                char c = meth_desc[i];
                n_args++;
                if (c == 'L') {
                    while (meth_desc[++i] != ';');
                }
                else if (c == '[') {
                    while (meth_desc[++i] == '[');
                    if (meth_desc[i] == 'L') {
                        while (meth_desc[++i] != ';');
                    }
                }
                i++;
            }

            std::vector < Variable * > args;
            for (uint16_t i = 0; i < n_args; i++) {
                args.insert(args.begin(), operands->top());
                operands->pop();
                if (args[0]->tag == Variable::type::_double || args[0]->tag == Variable::type::_long) {
                    args.insert(args.begin() + 1, new Variable());
                }
            }

            JavaClassInstance *staticInstance = Heap::getInstance()->getInstantiatedClass(cl_name);

            Leitor *jClass = staticInstance->javaClass;
            u2 aux;
            for(aux = 0; aux < jClass->get(METHODS_COUNT); aux++){
                std::string name = jClass->getUTF8(jClass->getMethods()->methods[aux]->name_index);
                std::string desc = jClass->getUTF8(jClass->getMethods()->methods[aux]->descriptor_index);
                if(name.compare(meth_name) == 0 && desc.compare(meth_desc) == 0)
                    break;
            }

            Frame *newFrame = new Frame(staticInstance->javaClass, cp, aux, staticInstance, &args);
            Heap::getInstance()->pushFrame(newFrame);
        }
        else {
            // se nao foi implementada
            exit(1);
        }
    };
    OPCODE_CB(0xB9){
        // INVOKEINTERFACE
        throw "Instruction 0xB9 not implemented yet.\n";
    };
    OPCODE_CB(0xBA){
        // INVOKEDYNAMIC
        throw "Instruction 0xBA not implemented yet.\n";
    };
    OPCODE_CB(0xBB){
        // NEW
        (*pc)++;

        uint16_t aux = code[(*pc)++];
        uint16_t idx = (aux << 8) + code[(*pc)++];
        uint16_t nameIndex = cp->getCpInfoElement(idx).constant_element.c1->name_index;

        std::string s = "L";
        s += std::string((char *) cp->getCpInfoElement(nameIndex).constant_element.c11->bytes, (size_t) cp->getCpInfoElement(nameIndex).constant_element.c11->length);

        if (s == "Ljava/lang/StringBuilder") {
            Variable *var = new Variable("Ljava/lang/String;");
            operands->push(var);
        }
        else {
            s += ";";

            Variable *var = new Variable(s);
            std::string className = "";
            for(unsigned int i = 1; i < s.length()-1; i++)
                className += s.at(i);
            JavaClassInstance *javaInstance = Heap::getInstance()->getInstantiatedClass(className);
            Heap::getInstance()->addInstanceFields(javaInstance);
            // TODO: maybe throw an exception if var->object is NULL

            operands->push(var);
        }
    };
    OPCODE_CB(0xBC){
        // NEWARRAY
        (*pc)++;

        int cont = *operands->top()->variable->intValue;
        operands->pop();

        Variable *type = new Variable("[");
        uint8_t atype = code[(*pc)++];
        switch (atype) {
            // T_BOOLEAN
            case 4:
                for (int i = 0; i < cont; i++) {
                    type->array->array->push_back(new Variable("Z"));
                }
                break;
            // T_CHAR
            case 5:
                for (int i = 0; i < cont; i++) {
                    type->array->array->push_back(new Variable("C"));
                }
                break;
            // T_FLOAT
            case 6:
                for (int i = 0; i < cont; i++) {
                    type->array->array->push_back(new Variable("F"));
                }
                break;
            // T_DOUBLE
            case 7:
                for (int i = 0; i < cont; i++) {
                    type->array->array->push_back(new Variable("D"));
                }
                break;
            // T_BYTE
            case 8:
                for (int i = 0; i < cont; i++) {
                    type->array->array->push_back(new Variable("B"));
                }
                break;
            // T_SHORT
            case 9:
                for (int i = 0; i < cont; i++) {
                    type->array->array->push_back(new Variable("S"));
                }
                break;
            // T_INT
            case 10:
                for (int i = 0; i < cont; i++) {
                    type->array->array->push_back(new Variable("I"));
                }
                break;
            // T_LONG
            case 11:
                for (int i = 0; i < cont; i++) {
                    type->array->array->push_back(new Variable("J"));
                }
                break;
        }
        operands->push(type);
    };
    OPCODE_CB(0xBD){
        // ANEWARRAY
        (*pc)++;

        uint16_t aux = code[(*pc)++];
        uint16_t idx = (aux << 8) + code[(*pc)++];
        uint16_t nameIndex = cp->getCpInfoElement(idx).constant_element.c1->name_index;

        std::string s = "L";
        s += std::string((char *) cp->getCpInfoElement(nameIndex).constant_element.c11->bytes, (size_t) cp->getCpInfoElement(nameIndex).constant_element.c11->length);
        s += ";";

        int cont = *operands->top()->variable->intValue;
        operands->pop();

        Variable *var = new Variable(s);
        if (cp->getCpInfoElement(idx).tag == 0x07 || cp->getCpInfoElement(idx).tag == 0x0B) {
            for (int i = 0; i < cont; i++) {
                var->array->array->push_back(new Variable(s));
            }
        }
        operands->push(var);
    };
    OPCODE_CB(0xBE){
        // ARRAYLENGTH
        (*pc)++;

        Variable *top = operands->top();
        operands->pop();

        if (top == 0) {
            throw "NullPointerException.\n";
            exit (1);
        }

        Variable *var = new Variable("I");
        *var->variable->intValue = (int) top->array->array->size();
        operands->push(var);
    };
    OPCODE_CB(0xBF){
        // ATHROW
        throw "Instruction 0xBF not implemented yet.\n";
    };
    OPCODE_CB(0xC0){
        // CHECKCAST
        throw "Instruction 0xC0 not implemented yet.\n";
    };
    OPCODE_CB(0xC1){
        // INSTANCEOF
        throw "Instruction 0xC1 not implemented yet.\n";
    };
    OPCODE_CB(0xC2){
        // MONITORENTER
        throw "Instruction 0xC2 not implemented yet.\n";
    };
    OPCODE_CB(0xC3){
        // MONITOREXIT
        throw "Instruction 0xC3 not implemented yet.\n";
    };
    OPCODE_CB(0xC4){
        // WIDE
        throw "Instruction 0xC4 not implemented yet.\n";
    };
    OPCODE_CB(0xC5){
        // MULTIANEWARRAY
        (*pc)++;

        uint16_t aux = code[(*pc)++];
        uint16_t idx = (aux << 8) + code[(*pc)++];
        uint8_t  dim = code[(*pc)++];

        std::stack < int > count_stack;
        for (uint8_t i = 0; i < dim; i++) {
            count_stack.push(*operands->top()->variable->intValue);
            operands->pop();
        }

        Variable *var = new Variable("[");
        uint16_t nameIndex = cp->getCpInfoElement(idx).constant_element.c1->name_index;
        std::string s((char *) cp->getCpInfoElement(nameIndex).constant_element.c11->bytes, (size_t) cp->getCpInfoElement(nameIndex).constant_element.c11->length);
        s += std::to_string(dim);

        Frame::newMultiDimensionalArray(var->array, count_stack, s);
        operands->push(var);
    };
    OPCODE_CB(0xC6){
        // IFNULL
        Variable *var = operands->top();
        operands->pop();

        if (var == 0) {
            uint16_t aux = code[(*pc) + 1];
            uint16_t branch = (aux << 8) + code[(*pc) + 2];
            *pc += branch;
        }
        else {
            *pc += 3;
        }
    };
    OPCODE_CB(0xC7){
        // IFNONNULL
        Variable *var = operands->top();
        operands->pop();

        if (var != 0) {
            uint16_t aux = code[(*pc) + 1];
            uint16_t branch = (aux << 8) + code[(*pc) + 2];
            *pc += branch;
        }
        else {
            *pc += 3;
        }
    };
    OPCODE_CB(0xC8){
        // GOTO_W
        throw "Instruction 0xC8 not implemented yet.\n";
    };
    OPCODE_CB(0xC9){
        // JSR_W
        throw "Instruction 0xC9 not implemented yet.\n";
    };
}

Frame::Frame(Leitor *jClass, Cp_info *cp, u2 methodIndex, JavaClassInstance *jClassInstance, std::vector<Variable*> *args){
    // Recebe a referência do método
    u2 i;
    for(i = 0; i < jClass->get(CONSTANT_POOL_COUNT); i++){
        if(jClass->getConstantPool()->getCpInfoElement(i).tag == CONSTANT_Methodref){
            if((jClass->getMethods()->methods[methodIndex]->name_index == jClass->getConstantPool()->getCpInfoElement(jClass->getConstantPool()->getCpInfoElement(i).constant_element.c2->name_and_type_index).constant_element.c10->name_index)
                && (jClass->getMethods()->methods[methodIndex]->descriptor_index == jClass->getConstantPool()->getCpInfoElement(jClass->getConstantPool()->getCpInfoElement(i).constant_element.c2->name_and_type_index).constant_element.c10->descriptor_index))
                break;
        }
    }
    //@@ cp_info *method = &cp[i];
    _pc = 0;

    std::string methodName = jClass->getUTF8(cp->getCpInfoElement(cp->getCpInfoElement(i).constant_element.c2->name_and_type_index ).constant_element.c10->name_index);
    std::string methodType = jClass->getUTF8(cp->getCpInfoElement(cp->getCpInfoElement(i).constant_element.c2->name_and_type_index ).constant_element.c10->descriptor_index);
    
    _jClass = jClass;
    _classInstance = jClassInstance;

    // Procura pelo método na classe
    for(_methodIndex = 0; _methodIndex < jClass->get(METHODS_COUNT); ++_methodIndex){
        std::string name = jClass->getUTF8(jClass->getMethods()->methods[_methodIndex]->name_index);
        std::string type = jClass->getUTF8(jClass->getMethods()->methods[_methodIndex]->descriptor_index);

        if(name.compare(methodName) == 0 && type.compare(methodType) == 0)
            break;    
    }

    if(_methodIndex == jClass->get(METHODS_COUNT))
        return;

    // Procura pelo código do método
    // Pode não haver exeções
    _exceptions = NULL;
    for(u2 i = 0; i < jClass->getMethods()->methods[_methodIndex]->attributes_count; i++){
        std::string aux = jClass->getUTF8(jClass->getMethods()->methods[_methodIndex]->attributes[i].getAttributeNameIndex());
        if(aux.compare("Code") == 0)
            _code = &jClass->getMethods()->methods[_methodIndex]->attributes[i];
        if(aux.compare("Exceptions") == 0)
            *_exceptions = jClass->getMethods()->methods[_methodIndex]->attributes[i];
    }

    // Define o tamanho do array e as variáveis locais
    this->_localVariables.resize(_code->getInfoElement()->codeAttr->max_locals);
    for(unsigned int i = 0; i < args->size(); i++)
        _localVariables[i] = args->at(i);
}

Frame::Frame(Leitor *jClass, Cp_info *cp, u2 method_index, JavaClassInstance *jClassInstance){
    _jClass = jClass;
    _methodIndex = method_index;
    _pc = 0;

    // Procura pelo código do método
    // Pode não haver exeções
    _exceptions = NULL;
    for(u2 i = 0; i < jClass->getMethods()->methods[_methodIndex]->attributes_count; i++){
        std::string aux = jClass->getUTF8(jClass->getMethods()->methods[_methodIndex]->attributes[i].getAttributeNameIndex());
        if(aux.compare("Code") == 0)
            _code = &jClass->getMethods()->methods[_methodIndex]->attributes[i];
        if(aux.compare("Exceptions") == 0)
            *_exceptions = jClass->getMethods()->methods[_methodIndex]->attributes[i];
    }
    
    // Define o tamanho do array e as variáveis locais
    _localVariables.resize(_code->getInfoElement()->codeAttr->max_locals);
    for(u2 i = 0; i < jClass->get(FIELDS_COUNT); i++)
        _localVariables[i] = new Variable(jClass->getUTF8(jClass->getFields()->fields[i]->descriptor_index));

    _classInstance = jClassInstance;
}

Frame::~Frame(){
    // TODO
}

void Frame::executeFrame(){
    op_func_cb current_cb_func_ptr;
    u1 current_opcode;

    current_opcode = *(_code->getInfoElement()->codeAttr->code + _pc);
    printf("opcode: %x\n", current_opcode);
    current_cb_func_ptr = op_impl_set[current_opcode];

    if (current_cb_func_ptr != nullptr){
        if (dbgpExecFlow){
            printf("(I) PC: %d, OPC: %x \n", _pc, current_opcode);
        }
        current_cb_func_ptr(_code->getInfoElement()->codeAttr->code, &_pc, &_operandStack, &_localVariables, _jClass->getConstantPool(), _classInstance);
    } else {
        printf("(E) Opcode %x not implemented\n", current_opcode);
        throw std::runtime_error("OpcodeNotImplementedError");
    }
}

Variable* Frame::constPoolRef(JavaClassInstance* jci, u2 index){
    // asm95@2018-11-24: based on ClassPrinter::constPoolRef

    u1 tag;
    Cp_info *current_cp;
    u4 u4_storage;
    u8 u8_storage;
    std::string *str_storage;
    Variable* dest_var = nullptr;

    current_cp = jci->javaClass->getConstantPool();
    tag = current_cp->getCpInfoElement(index).tag;
    switch (tag)
    {
        // asm95@2018-11-24: issue #2
        case CONSTANT_Integer:
            u4_storage = current_cp->getCpInfoElement(index).constant_element.c6->bytes;
            dest_var = new Variable("I", &u4_storage);
            break;
        case CONSTANT_Float:
            u4_storage = current_cp->getCpInfoElement(index).constant_element.c6->bytes;
            dest_var = new Variable("F", &u4_storage);
            break;
        case CONSTANT_Long:
            u8_storage = ((u8)current_cp->getCpInfoElement(index).constant_element.c9->high_bytes << 32) + current_cp->getCpInfoElement(index).constant_element.c9->low_bytes;
            dest_var = new Variable("J", &u8_storage);
            break;
        case CONSTANT_Double:
            u8_storage = ((u8)current_cp->getCpInfoElement(index).constant_element.c9->high_bytes << 32) + current_cp->getCpInfoElement(index).constant_element.c9->low_bytes;
            dest_var = new Variable("D", &u8_storage);
            break;
        case CONSTANT_String:
            str_storage = new std::string( jci->javaClass->getUTF8(
                current_cp->getCpInfoElement(index).constant_element.c5->string_index
            ));
            dest_var = new Variable("Ljava/lang/String;", str_storage);
            break;
        default:
            throw std::runtime_error(
                "(E) Not implemented tag (" +
                std::to_string(tag) +
                ")"
            );
            break;
    }

    return dest_var;
}

void Frame::pushOpStack(std::stack<Variable*> *operands, Variable * var) {
    operands->push(var);
}

void Frame::newMultiDimensionalArray(arrayVariable *arr, std::stack < int > st, std::string s) {
    int n = st.top();
    st.pop();

    if (!st.empty()) {
        for (int i = 0; i < n; i++) {
            Variable *var = new Variable("[");
            newMultiDimensionalArray(var->array, st, s);
            arr->array->push_back(var);
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            Variable *var = new Variable(s);
            arr->array->push_back(var);
        }
    }
}

std::stack<Variable*>* Frame::getStack(){
    return &_operandStack;
}
