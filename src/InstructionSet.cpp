#include "../include/InstructionSet.hpp"

InstructionSet::InstructionSet(){
	mnem[0x00] = "NOP";
	mnem[0x01] = "ACONST_NULL";
	mnem[0x02] = "ICONST_M1";
	mnem[0x03] = "ICONST_0";
	mnem[0x04] = "ICONST_1";
	mnem[0x05] = "ICONST_2";
	mnem[0x06] = "ICONST_3";
	mnem[0x07] = "ICONST_4";
	mnem[0x08] = "ICONST_5";
	mnem[0x09] = "LCONST_0";
	mnem[0x0A] = "LCONST_1";
	mnem[0x0B] = "FCONST_0";
	mnem[0x0C] = "FCONST_1";
	mnem[0x0D] = "FCONST_2";
	mnem[0x0E] = "DCONST_0";
	mnem[0x0F] = "DCONST_1";
	mnem[0x10] = "BIPUSH";
	mnem[0x11] = "SIPUSH";
	mnem[0x12] = "LDC";
	mnem[0x13] = "LDC_W";
	mnem[0x14] = "LDC2_W";
	mnem[0x15] = "ILOAD";
	mnem[0x16] = "LLOAD";
	mnem[0x17] = "FLOAD";
	mnem[0x18] = "DLOAD";
	mnem[0x19] = "ALOAD";
	mnem[0x1A] = "ILOAD_0";
	mnem[0x1B] = "ILOAD_1";
	mnem[0x1C] = "ILOAD_2";
	mnem[0x1D] = "ILOAD_3";
	mnem[0x1E] = "LLOAD_0";
	mnem[0x1F] = "LLOAD_1";
	mnem[0x20] = "LLOAD_2";
	mnem[0x21] = "LLOAD_3";
	mnem[0x22] = "FLOAD_0";
	mnem[0x23] = "FLOAD_1";
	mnem[0x24] = "FLOAD_2";
	mnem[0x25] = "FLOAD_3";
	mnem[0x26] = "DLOAD_0";
	mnem[0x27] = "DLOAD_1";
	mnem[0x28] = "DLOAD_2";
	mnem[0x29] = "DLOAD_3";
	mnem[0x2A] = "ALOAD_0";
	mnem[0x2B] = "ALOAD_1";
	mnem[0x2C] = "ALOAD_2";
	mnem[0x2D] = "ALOAD_3";
	mnem[0x2E] = "IALOAD";
	mnem[0x2F] = "LALOAD";
	mnem[0x30] = "FALOAD";
	mnem[0x31] = "DALOAD";
	mnem[0x32] = "AALOAD";
	mnem[0x33] = "BALOAD";
	mnem[0x34] = "CALOAD";
	mnem[0x35] = "SALOAD";
	mnem[0x36] = "ISTORE";
	mnem[0x37] = "LSTORE";
	mnem[0x38] = "FSTORE";
	mnem[0x39] = "DSTORE";
	mnem[0x3A] = "ASTORE";
	mnem[0x3B] = "ISTORE_0";
	mnem[0x3C] = "ISTORE_1";
	mnem[0x3D] = "ISTORE_2";
	mnem[0x3E] = "ISTORE_1";
	mnem[0x3F] = "LSTORE_0";
	mnem[0x40] = "LSTORE_1";
	mnem[0x41] = "LSTORE_2";
	mnem[0x42] = "LSTORE_3";
	mnem[0x43] = "FSTORE_0";
	mnem[0x44] = "FSTORE_1";
	mnem[0x45] = "FSTORE_2";
	mnem[0x46] = "FSTORE_3";
	mnem[0x47] = "DSTORE_0";
	mnem[0x48] = "DSTORE_1";
	mnem[0x49] = "DSTORE_2";
	mnem[0x4A] = "DSTORE_3";
	mnem[0x4B] = "ASTORE_0";
	mnem[0x4C] = "ASTORE_1";
	mnem[0x4D] = "ASTORE_2";
	mnem[0x4E] = "ASTORE_3";
	mnem[0x4F] = "IASTORE";
	mnem[0x50] = "LASTORE";
	mnem[0x51] = "FASTORE";
	mnem[0x52] = "DASTORE";
	mnem[0x53] = "AASTORE";
	mnem[0x54] = "BASTORE";
	mnem[0x55] = "CASTORE";
	mnem[0x56] = "SASTORE";
	mnem[0x57] = "POP";
	mnem[0x58] = "POP2";
	mnem[0x59] = "DUP";
	mnem[0x5A] = "DUP_X1";
	mnem[0x5B] = "DUP_X2";
	mnem[0x5C] = "DUP2";
	mnem[0x5D] = "DUP2_X1";
	mnem[0x5E] = "DUP2_X2";
	mnem[0x5F] = "SWAP";
	mnem[0x60] = "IADD";
	mnem[0x61] = "LADD";
	mnem[0x62] = "FADD";
	mnem[0x63] = "DADD";
	mnem[0x64] = "ISUB";
	mnem[0x65] = "LSUB";
	mnem[0x66] = "FSUB";
	mnem[0x67] = "DSUB";
	mnem[0x68] = "IMUL";
	mnem[0x69] = "LMUL";
	mnem[0x6A] = "FMUL";
	mnem[0x6B] = "DMUL";
	mnem[0x6C] = "IDIV";
	mnem[0x6D] = "LDIV";
	mnem[0x6E] = "FDIV";
	mnem[0x6F] = "DDIV";
	mnem[0x70] = "IREM";
	mnem[0x71] = "LREM";
	mnem[0x72] = "FREM";
	mnem[0x73] = "DREM";
	mnem[0x74] = "INEG";
	mnem[0x75] = "LNEG";
	mnem[0x76] = "FNEG";
	mnem[0x77] = "DNEG";
	mnem[0x78] = "ISHL";
	mnem[0x79] = "LSHL";
	mnem[0x7A] = "ISHR";
	mnem[0x7B] = "LSHR";
	mnem[0x7C] = "IUSHR";
	mnem[0x7D] = "LUSHR";
	mnem[0x7E] = "IAND";
	mnem[0x7F] = "LAND";
	mnem[0x80] = "IOR";
	mnem[0x81] = "LOR";
	mnem[0x82] = "IXOR";
	mnem[0x83] = "LXOR";
	mnem[0x84] = "IINC";
	mnem[0x85] = "I2L";
	mnem[0x86] = "I2F";
	mnem[0x87] = "I2D";
	mnem[0x88] = "L2I";
	mnem[0x89] = "L2F";
	mnem[0x8A] = "L2D";
	mnem[0x8B] = "F2I";
	mnem[0x8C] = "F2L";
	mnem[0x8D] = "F2D";
	mnem[0x8E] = "D2I";
	mnem[0x8F] = "D2L";
	mnem[0x90] = "D2F";
	mnem[0x91] = "I2B";
	mnem[0x92] = "I2C";
	mnem[0x93] = "I2S";
	mnem[0x94] = "LCMP";
	mnem[0x95] = "FCMPL";
	mnem[0x96] = "FCMPG";
	mnem[0x97] = "DCMPL";
	mnem[0x98] = "DCMPG";
	mnem[0x99] = "IFEQ";
	mnem[0x9A] = "IFNE";
	mnem[0x9B] = "IFLT";
	mnem[0x9C] = "IFGE";
	mnem[0x9D] = "IFGT";
	mnem[0x9E] = "IFLE";
	mnem[0x9F] = "IF_ICMPEQ";
	mnem[0xA0] = "IF_ICMPNE";
	mnem[0xA1] = "IF_ICMPLT";
	mnem[0xA2] = "IF_ICMPGE";
	mnem[0xA3] = "IF_ICMPGT";
	mnem[0xA4] = "IF_ICMPLE";
	mnem[0xA5] = "IF_ACMPEQ";
	mnem[0xA6] = "IF_ACMPNE";
	mnem[0xA7] = "GOTO";
	mnem[0xA8] = "JSR";
	mnem[0xA9] = "RET";
	mnem[0xAA] = "TABLESWITCH";
	mnem[0xAB] = "LOOKUPSWITCH";
	mnem[0xAC] = "IRETURN";
	mnem[0xAD] = "LRETURN";
	mnem[0xAE] = "FRETURN";
	mnem[0xAF] = "DRETURN";
	mnem[0xB0] = "ARETURN";
	mnem[0xB1] = "RETURN";
	mnem[0xB2] = "GETSTATIC";
	mnem[0xB3] = "PUTSTATIC";
	mnem[0xB4] = "GETFIELD";
	mnem[0xB5] = "PUTFIELD";
	mnem[0xB6] = "INVOKEVIRTUAL";
	mnem[0xB7] = "INVOKESPECIAL";
	mnem[0xB8] = "INVOKESTATIC";
	mnem[0xB9] = "INVOKEINTERFACE";
	mnem[0xBA] = "INVOKEDYNAMIC";
	mnem[0xBB] = "NEW";
	mnem[0xBC] = "NEWARRAY";
	mnem[0xBD] = "ANEWARRAY";
	mnem[0xBE] = "ARRAYLENGTH";
	mnem[0xBF] = "ATHROW";
	mnem[0xC0] = "CHECKCAST";
	mnem[0xC1] = "INSTANCEOF";
	mnem[0xC2] = "MONITORENTER";
	mnem[0xC3] = "MONITOREXIT";
	mnem[0xC4] = "WIDE";
	mnem[0xC5] = "MULTIANEWARRAY";
	mnem[0xC6] = "IFNULL";
	mnem[0xC7] = "IFNONNULL";
	mnem[0xC8] = "GOTO_W";
	mnem[0xC9] = "JSR_W";
}

string InstructionSet::get(int key)
{
	return mnem[key];
}

void InstructionSet::PrintInstr(u1 bcode)
{
	cout << "Instruction : " << mnem[bcode] << endl;
}

//void printInstr(Leitor *l)
//{


	//Method_info * mts = l->getMethods();
	//int tam = sizeof(mts)/sizeof(mts[0]);

	/*for(int i=0;i < tam,i++){
		mts[i];
	}*/

	/*switch(key)
	{
		case 0x00:
		   cout << "-> null" << endl;
		case 0x01:
		   cout << " -> null" << endl;
		case 0x02:
			cout << " -> 0" << endl;
		case 0x03:
			cout << " -> 1" << endl;
		case 0x04:
			cout << " -> 2" << endl;
		case 0x05:
			cout << " -> 3" << endl;
		case 0x06:
			cout << " -> 4" << endl;
		case 0x07:
			cout << " -> 5" << endl;
		case 0x08:
		case 0x09:
		case 0x0A:
		case 0x0B:
		case 0x0C:
		case 0x0D:
		case 0x0E:
		case 0x0F:
		case 0x10:
		case 0x11:
		case 0x12:
		case 0x13:
		case 0x14:
		case 0x15:
		case 0x16:
		case 0x17:
		case 0x18:
		case 0x19:
		case 0x1A:
		case 0x1B:
		case 0x1C:
		case 0x1D:
		case 0x1F:
		case 0x20:
		case 0x21:
		case 0x22:
		case 0x23:
		case 0x24:
		case 0x25:
		case 0x26:
		case 0x27:
		case 0x28:
		case 0x29:
		case 0x2A:
		case 0x2B:
		case 0x2C:
		case 0x2D:
		case 0x2E:
		case 0x2F:
		case 0x30:
		case 0x31:
		case 0x32:
		case 0x33:
		case 0x34:
		case 0x35:
		case 0x36:
		case 0x37:
		case 0x38:
		case 0x39:
		case 0x3A:
		case 0x3B:
		case 0x3C:
		case 0x3D:
		case 0x3E:
		case 0x3F:
		case 0x40:
		case 0x41:
		case 0x42:
		case 0x43:
		case 0x44:
		case 0x45:
		case 0x46:
		case 0x47:
		case 0x48:
		case 0x49:
		case 0x4A:
		case 0x4B:
		case 0x4C:
		case 0x4D:
		case 0x4E:
		case 0x4F:
		case 0x50:
		case 0x51:
		case 0x52:
		case 0x53:
		case 0x54:
		case 0x55:
		case 0x56:
		case 0x57:
		case 0x58:
		case 0x59:
		case 0x5A:
		case 0x5B:
		case 0x5C:
		case 0x5D:
		case 0x5E:
		case 0x5F:
		case 0x60:
		case 0x61:
		case 0x62:

*/
	//}
//}