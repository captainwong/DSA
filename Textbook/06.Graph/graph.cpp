#include "../../include/test/test_graph.h"

using namespace dtl;

int main(int /*argc*/, char** /*argv*/)
{
	//test::testGraph(10, 2, dtl::WAIT_PAUSE);
	test::testGraph("../../_input/Graph_Matrix/graph.prim.0009+0028.txt"/*, dtl::WAIT_PAUSE*/);

	return 0;
}
