#include <unistd.h>
#include <cstring>

class N {
public:
	int nb;
	int (N::*func)(N &);
	char annotation[100];

	N(int val) : nb(val)
	{
		this->func = &N::operator+;
	}
	int operator+(N &right)
	{
		return this->nb + right.nb;
	}
	int operator-(N &right)
	{
		return this->nb - right.nb;
	}
	void setAnnotation(char *str)
	{
		memcpy(this->annotation, str, strlen(str));
	}
};

int main(int argc,char **argv) {
	N *a;
	N *b;

	if (argc < 2) {
		_exit(1);
	}


	a = new N(5);
	b = new N(6);
	a->setAnnotation(argv[1]);

	return b->operator+(*a);
}