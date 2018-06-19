#include <iostream>
#include "BrainTree.h"

namespace bt = BrainTree;

class SayHello : public bt::Node
{
    Status update() override
    {
        std::cout << "Hello, World!" << std::endl;
        return Node::Status::Success;
    }
};

int main()
{
    bt::BehaviorTree tree;

    auto repeater = std::make_shared<bt::Repeater>(5);
    repeater->setChild(std::make_shared<SayHello>());
    tree.setRoot(repeater);

    // simulate 5 frames
    for (int i = 0; i < 5; i++)
        tree.update();

    return 0;
}
