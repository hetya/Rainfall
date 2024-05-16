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
	N *v6;
	N *v4;

	if (ac < 2) {
		_exit(1);
	}


	v6 = new N(5);
	v4 = new N(6);
	v6->setAnnotation(av[1]);

	return v4->operator+(*v6);
}