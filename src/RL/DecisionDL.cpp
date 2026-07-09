#include "DecisionDL.h"

#include <algorithm>

#include "FeatureEngineering.h"

#include <iostream>

//====================================================
// CONSTRUCTOR
//====================================================

DecisionDL::DecisionDL()
{
}

//====================================================
// INITIALIZE
//====================================================

void DecisionDL::initialize(
    uint32_t inputSize_,
    uint32_t hiddenSize1_,
    uint32_t hiddenSize2_)
{
    if (initialized)
        return;

    inputSize   = inputSize_;
    hiddenSize1 = hiddenSize1_;
    hiddenSize2 = hiddenSize2_;

    model = torch::nn::Sequential(

        torch::nn::Linear(
            inputSize,
            hiddenSize1),

        torch::nn::ReLU(),

        torch::nn::Linear(
            hiddenSize1,
            hiddenSize2),

        torch::nn::ReLU(),

        torch::nn::Linear(
            hiddenSize2,
            1)
    );

    register_module(
        "model",
        model);

    initialized = true;
}

//====================================================
// FORWARD
//====================================================

torch::Tensor DecisionDL::forward(
    torch::Tensor input)
{
    return model->forward(input);
}

//====================================================
// ENCODE NODES
//====================================================

torch::Tensor DecisionDL::encodeNodes(
    const GameState& state,
    const std::vector<DecisionNode>& nodes)
{
    if (nodes.empty())
    {
        return torch::empty(
            {0, static_cast<int64_t>(inputSize)});
    }

    std::vector<float> data;

    data.reserve(
        nodes.size() * inputSize);

    for (const DecisionNode& node : nodes)
    {
        std::vector<float> features =
            FeatureEngineering::encode(
                state,
                node);

        data.insert(
            data.end(),
            features.begin(),
            features.end());
    }

    auto tensor =
        torch::from_blob(
            data.data(),
            {
                static_cast<int64_t>(nodes.size()),
                static_cast<int64_t>(inputSize)
            },
            torch::kFloat);

    return tensor.clone();
}

//====================================================
// EVALUATE
//====================================================

torch::Tensor DecisionDL::evaluate(
    const GameState& state,
    const std::vector<DecisionNode>& nodes)
{
    torch::Tensor input =
        encodeNodes(
            state,
            nodes);


    torch::Tensor output =
        forward(input);


    std::cout
        << "[RL] Q values: "
        << output
        << std::endl;


    return output;
}

//====================================================
// BEST MOVE
//====================================================

uint32_t DecisionDL::bestMove(
    const GameState& state,
    const std::vector<DecisionNode>& nodes)
{
    if (nodes.empty())
        return 0;


    torch::Tensor scores =
        evaluate(
            state,
            nodes);


    return static_cast<uint32_t>(
        scores.argmax().item<int64_t>()
    );
}