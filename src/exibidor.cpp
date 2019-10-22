#include "../include/exibidor.hpp"
using namespace std;

Exibidor::Exibidor(Leitor l)
{
	r = l;
}

void Exibidor::GeneralInformation()
{
	printf("Minor version: %x\n", r.getMinorVersion());
	printf("Major version: %x\n", r.getMajorVersion());
	printf("Constant pool count: %d\n", r.getConstantPoolCount());
	printf("Acess Flags: %x\n", r.getAcessFlags());
	printf("This Class: ");
	printf("Super Class: ");
	printf("Interfaces count: %d\n",r.getInterfacesCount());
	printf("Fields Count: %d\n",r.getFieldsCount());
	printf("Methods Count: %d\n",r.getMethodsCount());
	printf("Attributes Count: %d\n",r.getAttributesCount());
}

void Exibidor::ConstantPool()
{
	
}

void Exibidor::Interfaces()
{

}

void Exibidor::Fields()
{
	printf("Show Fields:\n");
	cout << "Public: " << PUBLIC << endl;
	cout << "Private: " << PRIVATE << endl;
	cout << "Protected: " << PROTECTED << endl;
	cout << "Static: " << STATIC << endl;
	cout << "Volatile: " << VOLATILE << endl;
	cout << "Transient: " << TRANSIENT << endl;
	cout << "Synthetic: " << SYNTHETIC << endl;
	cout << "Enum: " << ENUM << endl;
	cout << "All: " << ALL << endl;
	
	scanf("%d\n",&show);

	ShowField(show);
}

void Exibidor::ShowField(int s = ALL)
{
	/*fazer um loop para cada field e ir exibindo esses atributos com o filtro correspondente*/
	printf("Name:\n");
	printf("Descriptor:\n");
	printf("AcessFlags:\n");
}

void Exibidor::Methods()
{
  printf("Show Methods:\n");
  cout << "Public: " << PUBLIC << endl;
  cout << "Private: " << PRIVATE << endl;
  cout << "Static: " << STATIC << endl;
  cout << "Final: " << FINAL << endl;
  cout << "Native: " << NATIVE << endl;
  cout << "Abstract: " << ABSTRACT << endl; 
  cout << "Strict: " << STRICT << endl;
  cout << "Synthetic: " << SYNTHETIC << endl;
  cout << "Bridge: " << BRIDGE << endl;
  cout << "Varargs: " << VARARGS << endl;
  cout << "All: " << ALL << endl;
  
  scanf("%d\n",&show);

	ShowMethod(show);
}

void Exibidor::ShowMethod(int s = ALL)
{
	printf("Name:\n");
	printf("Descriptor:\n");
	printf("AcessFlags:\n");
}

void Exibidor::Attributes()
{

}