#include <QApplication>
#include "CGraph/src/CGraph.h"

using namespace CGraph;
class VisionNode final : public CGraph::GNode {

public:
    CStatus run() override {
        std::cout << "Running..." << std::endl;
        return CStatus();
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    auto pipeline = CGraph::GPipelineFactory::create();
    GElementPtr a = nullptr;
    pipeline->registerGElement<VisionNode>(&a);
    pipeline->process();
    GPipelineFactory::clear();
    return QApplication::exec();
}
