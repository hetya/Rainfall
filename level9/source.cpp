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

int		main(int argc, char **argv)
{
    if (argc > 1)
    {
        N *buff = new N(5);


        N *buff_1 = new N(6);

        buff->setAnnotation(argv[1]);
        return (buff_1->*(buff_1->func))(*buff);
    }
    _exit(1);
}