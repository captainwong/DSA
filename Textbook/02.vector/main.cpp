
#include "../include/dtl/vector.h"
#include "../include/test/test_vector.h"

using namespace dtl;

int main(int argc, char* argv[])
{
	test::testVector<int>(10, WAIT_NO_WAIT);
	wait(-1);
	return 0;
}
