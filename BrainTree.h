// BrainTree - A C++ behavior tree single header library.
// Copyright 2015-2018 Par Arvidsson. All rights reserved.
// Licensed under the MIT license (https://github.com/arvidsson/BrainTree/blob/master/LICENSE).

#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <cassert>

namespace BrainTree
{

class Blackboard
{
public:
    void setBool(std::string key, bool value) { bools[key] = value; }
    bool getBool(std::string key)
    {
        if (bools.find(key) == bools.end()) {
            bools[key] = false;
        }
        return bools[key];
    }
    bool hasBool(std::string key) const { return bools.find(key) != bools.end(); }

    void setInt(std::string key, int value)  { ints[key] = value; }
    int getInt(std::string key)
    {
        if (ints.find(key) == ints.end()) {
            ints[key] = 0;
        }
        return ints[key];
    }
    bool hasInt(std::string key) const  { return ints.find(key) != ints.end(); }

    void setFloat(std::string key, float value)  { floats[key] = value; }
    float getFloat(std::string key)
    {
        if (floats.find(key) == floats.end()) {
            floats[key] = 0.0f;
        }
        return floats[key];
    }
    bool hasFloat(std::string key) const  { return floats.find(key) != floats.end(); }

    void setDouble(std::string key, double value)  { doubles[key] = value; }
    double getDouble(std::string key)
    {
        if (doubles.find(key) == doubles.end()) {
            doubles[key] = 0.0f;
        }
        return doubles[key];
    }
    bool hasDouble(std::string key) const  { return doubles.find(key) != doubles.end(); }

    void setString(std::string key, std::string value)  { strings[key] = value; }
    std::string getString(std::string key)
    {
        if (strings.find(key) == strings.end()) {
            strings[key] = "";
        }
        return strings[key];
    }
    bool hasString(std::string key) const  { return strings.find(key) != strings.end(); }

    using Ptr = std::shared_ptr<Blackboard>;

protected:
    std::unordered_map<std::string, bool> bools;
    std::unordered_map<std::string, int> ints;
    std::unordered_map<std::string, float> floats;
    std::unordered_map<std::string, double> doubles;
    std::unordered_map<std::string, std::string> strings;
};

class Node
{
public:
    enum class Status
    {
        Invalid,
        Success,
        Failure,
        Running,
    };

    virtual ~Node() {}
    void setBlackboard(Blackboard::Ptr board) {
        blackboard = board;
    }
    Blackboard::Ptr getBlackboard() const { return blackboard; }

    virtual Status update() = 0;
    virtual void initialize() {}
    virtual void terminate(Status s) {}

    Status tick()
    {
        if (status != Status::Running) {
            initialize();
        }

        status = update();

        if (status != Status::Running) {
            terminate(status);
        }

        return status;
    }

    bool isSuccess() const { return status == Status::Success; }
    bool isFailure() const { return status == Status::Failure; }
    bool isRunning() const { return status == Status::Running; }
    bool isTerminated() const { return isSuccess() || isFailure(); }

    void reset() { status = Status::Invalid; }

    using Ptr = std::shared_ptr<Node>;

protected:
    Status status = Status::Invalid;
    Blackboard::Ptr blackboard = nullptr;
};

class Composite : public Node
{
public:
    virtual ~Composite() {}
    
    void addChild(Node::Ptr child) { children.push_back(child); it=children.begin(); }
    bool hasChildren() const { return !children.empty(); }
    
protected:
    std::vector<Node::Ptr> children;
    std::vector<Node::Ptr>::iterator it;
};

class Decorator : public Node
{
public:
    virtual ~Decorator() {}

    void setChild(Node::Ptr node) { child = node; }
    bool hasChild() const { return child != nullptr; }
    
protected:
    Node::Ptr child = nullptr;
};

class Leaf : public Node
{
public:
    Leaf() {}
    virtual ~Leaf() {}
    Leaf(Blackboard::Ptr blackboard) : blackboard(blackboard) {}
    
    virtual Status update() = 0;

protected:
    Blackboard::Ptr blackboard;
};

class BehaviorTree : public Node
{
public:
    BehaviorTree() {
        blackboard = std::make_shared<Blackboard>();
    }
    BehaviorTree(const Node::Ptr &rootNode) : BehaviorTree() { root = rootNode; }
    
    Status update() { return root->tick(); }
    
    void setRoot(const Node::Ptr &node) { root = node; }
    
private:
    Node::Ptr root = nullptr;
};

template <class Parent>
class DecoratorBuilder;

template <class Parent>
class CompositeBuilder
{
public:
    CompositeBuilder(Parent* parent, Composite* node) : parent(parent), node(node) {}

    template <class NodeType, typename... Args>
    CompositeBuilder<Parent> leaf(Args... args)
    {
        auto child = std::make_shared<NodeType>((args)...);
        child->setBlackboard(node->getBlackboard());
        node->addChild(child);
        return *this;
    }

    template <class CompositeType, typename... Args>
    CompositeBuilder<CompositeBuilder<Parent>> composite(Args... args)
    {
        auto child = std::make_shared<CompositeType>((args)...);
        child->setBlackboard(node->getBlackboard());
        node->addChild(child);
        return CompositeBuilder<CompositeBuilder<Parent>>(this, (CompositeType*)child.get());
    }

    template <class DecoratorType, typename... Args>
    DecoratorBuilder<CompositeBuilder<Parent>> decorator(Args... args)
    {
        auto child = std::make_shared<DecoratorType>((args)...);
        child->setBlackboard(node->getBlackboard());
        node->addChild(child);
        return DecoratorBuilder<CompositeBuilder<Parent>>(this, (DecoratorType*)child.get());
    }

    Parent& end()
    {
        return *parent;
    }

private:
    Parent * parent;
    Composite* node;
};

template <class Parent>
class DecoratorBuilder
{
public:
    DecoratorBuilder(Parent* parent, Decorator* node) : parent(parent), node(node) {}

    template <class NodeType, typename... Args>
    DecoratorBuilder<Parent> leaf(Args... args)
    {
        auto child = std::make_shared<NodeType>((args)...);
        child->setBlackboard(node->getBlackboard());
        node->setChild(child);
        return *this;
    }

    template <class CompositeType, typename... Args>
    CompositeBuilder<DecoratorBuilder<Parent>> composite(Args... args)
    {
        auto child = std::make_shared<CompositeType>((args)...);
        child->setBlackboard(node->getBlackboard());
        node->setChild(child);
        return CompositeBuilder<DecoratorBuilder<Parent>>(this, (CompositeType*)child.get());
    }

    template <class DecoratorType, typename... Args>
    DecoratorBuilder<DecoratorBuilder<Parent>> decorator(Args... args)
    {
        auto child = std::make_shared<DecoratorType>((args)...);
        child->setBlackboard(node->getBlackboard());
        node->setChild(child);
        return DecoratorBuilder<DecoratorBuilder<Parent>>(this, (DecoratorType*)child.get());
    }

    Parent& end()
    {
        return *parent;
    }

private:
    Parent * parent;
    Decorator* node;
};

class Builder
{
public:
    Builder() {
        tree = std::make_shared<BehaviorTree>();
    }
    template <class NodeType, typename... Args>
    Builder leaf(Args... args)
    {
        root = std::make_shared<NodeType>((args)...);
        root->setBlackboard(tree->getBlackboard());
        return *this;
    }

    template <class CompositeType, typename... Args>
    CompositeBuilder<Builder> composite(Args... args)
    {
        root = std::make_shared<CompositeType>((args)...);
        root->setBlackboard(tree->getBlackboard());
        return CompositeBuilder<Builder>(this, (CompositeType*)root.get());
    }

    template <class DecoratorType, typename... Args>
    DecoratorBuilder<Builder> decorator(Args... args)
    {
        root = std::make_shared<DecoratorType>((args)...);
        root->setBlackboard(tree->getBlackboard());
        return DecoratorBuilder<Builder>(this, (DecoratorType*)root.get());
    }

    Node::Ptr build()
    {
        assert(root != nullptr && "The Behavior Tree is empty!");
        tree->setRoot(root);
        return tree;
    }

private:
    Node::Ptr root;
    std::shared_ptr<BehaviorTree> tree;
};

// The Selector composite ticks each child node in order.
// If a child succeeds or runs, the selector returns the same status.
// In the next tick, it will try to run each child in order again.
// If all children fails, only then does the selector fail.
class Selector : public Composite
{
public:
    void initialize() override
    {
        it = children.begin();
    }

    Status update() override
    {
        assert(hasChildren() && "Composite has no children");

        while (it != children.end()) {
            auto status = (*it)->tick();

            if (status != Status::Failure) {
                return status;
            }

            it++;
        }

        return Status::Failure;
    }
};

// The Sequence composite ticks each child node in order.
// If a child fails or runs, the sequence returns the same status.
// In the next tick, it will try to run each child in order again.
// If all children succeeds, only then does the sequence succeed.
class Sequence : public Composite
{
public:
    void initialize() override
    {
        it = children.begin();
    }

    Status update() override
    {
        assert(hasChildren() && "Composite has no children");

        while (it != children.end()) {
            auto status = (*it)->tick();

            if (status != Status::Success) {
                return status;
            }

            it++;
        }

        return Status::Success;
    }
};

// The StatefulSelector composite ticks each child node in order, and remembers what child it prevously tried to tick.
// If a child succeeds or runs, the stateful selector returns the same status.
// In the next tick, it will try to run the next child or start from the beginning again.
// If all children fails, only then does the stateful selector fail.
class StatefulSelector : public Composite
{
public:
    Status update() override
    {
        assert(hasChildren() && "Composite has no children");

        while (it != children.end()) {
            auto status = (*it)->tick();

            if (status != Status::Failure) {
                return status;
            }

            it++;
        }

        it = children.begin();
        return Status::Failure;
    }
};

// The StatefulSequence composite ticks each child node in order, and remembers what child it prevously tried to tick.
// If a child fails or runs, the stateful sequence returns the same status.
// In the next tick, it will try to run the next child or start from the beginning again.
// If all children succeeds, only then does the stateful sequence succeed.
class StatefulSequence : public Composite
{
public:
    Status update() override
    {
        assert(hasChildren() && "Composite has no children");

        while (it != children.end()) {
            auto status = (*it)->tick();

            if (status != Status::Success) {
                return status;
            }

            it++;
        }

        it = children.begin();
        return Status::Success;
    }
};

class ParallelSequence : public Composite
{
public:
    ParallelSequence(bool successOnAll = true, bool failOnAll = true) : useSuccessFailPolicy(true), successOnAll(successOnAll), failOnAll(failOnAll) {}
    ParallelSequence(int minSuccess, int minFail) : minSuccess(minSuccess), minFail(minFail) {}

    Status update() override
    {
        assert(hasChildren() && "Composite has no children");

        int minimumSuccess = minSuccess;
        int minimumFail = minFail;

        if (useSuccessFailPolicy) {
            if (successOnAll) {
                minimumSuccess = children.size();
            }
            else {
                minimumSuccess = 1;
            }

            if (failOnAll) {
                minimumFail = children.size();
            }
            else {
                minimumFail = 1;
            }
        }

        int total_success = 0;
        int total_fail = 0;

        for (auto &child : children) {
            auto status = child->tick();
            if (status == Status::Success) {
                total_success++;
            }
            if (status == Status::Failure) {
                total_fail++;
            }
        }

        if (total_success >= minimumSuccess) {
            return Status::Success;
        }
        if (total_fail >= minimumFail) {
            return Status::Failure;
        }

        return Status::Running;
    }

private:
    bool useSuccessFailPolicy = false;
    bool successOnAll = true;
    bool failOnAll = true;
    int minSuccess = 0;
    int minFail = 0;
};

// The Succeeder decorator returns success, regardless of what happens to the child.
class Succeeder : public Decorator
{
public:
    Status update() override
    {
        child->tick();
        return Status::Success;
    }
};

// The Failer decorator returns failure, regardless of what happens to the child.
class Failer : public Decorator
{
public:
    Status update() override
    {
        child->tick();
        return Status::Failure;
    }
};

// The Inverter decorator inverts the child node's status, i.e. failure becomes success and success becomes failure.
// If the child runs, the Inverter returns the status that it is running too.
class Inverter : public Decorator
{
public:
    Status update() override
    {
        auto s = child->tick();

        if (s == Status::Success) {
            return Status::Failure;
        }
        else if (s == Status::Failure) {
            return Status::Success;
        }

        return s;
    }
};

// The Repeater decorator repeats infinitely or to a limit until the child returns success.
class Repeater : public Decorator
{
public:
    Repeater(int limit = 0) : limit(limit) {}

    void initialize() override
    {
        counter = 0;
    }

    Status update() override
    {
        child->tick();

        if (limit > 0 && ++counter == limit) {
            return Status::Success;
        }

        return Status::Running;
    }

protected:
    int limit;
    int counter = 0;
};

// The UntilSuccess decorator repeats until the child returns success and then returns success.
class UntilSuccess : public Decorator
{
public:
    Status update() override
    {
        while (1) {
            auto status = child->tick();

            if (status == Status::Success) {
                return Status::Success;
            }
        }
    }
};

// The UntilFailure decorator repeats until the child returns fail and then returns success.
class UntilFailure : public Decorator
{
public:
    Status update() override
    {
        while (1) {
            auto status = child->tick();

            if (status == Status::Failure) {
                return Status::Success;
            }
        }
    }
};

} // namespace BrainTree
