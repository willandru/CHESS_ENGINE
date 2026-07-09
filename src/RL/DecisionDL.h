#pragma once

#include <torch/torch.h>

#include <vector>
#include <cstdint>

#include "GameState.h"
#include "DecisionNode.h"

class DecisionDL : public torch::nn::Module
{
public:

    //------------------------------------------------
    // Constructor
    //------------------------------------------------

    DecisionDL();

    //------------------------------------------------
    // Creates the neural network
    //------------------------------------------------

    void initialize(
        uint32_t inputSize,
        uint32_t hiddenSize1,
        uint32_t hiddenSize2);

    //------------------------------------------------
    // Forward propagation
    //
    // Input:
    //     [N x inputSize]
    //
    // Output:
    //     [N x 1]
    //------------------------------------------------

    torch::Tensor forward(
        torch::Tensor input);

    //------------------------------------------------
    // Encodes all candidate nodes into one
    // input tensor.
    //
    // Output:
    //     [N x inputSize]
    //------------------------------------------------

    torch::Tensor encodeNodes(
        const GameState& state,
        const std::vector<DecisionNode>& nodes);

    //------------------------------------------------
    // Evaluates every candidate node.
    //
    // Output:
    //     [N x 1]
    //------------------------------------------------

    torch::Tensor evaluate(
        const GameState& state,
        const std::vector<DecisionNode>& nodes);

    //------------------------------------------------
    // Returns the index of the best node.
    //------------------------------------------------

    uint32_t bestMove(
        const GameState& state,
        const std::vector<DecisionNode>& nodes);

private:

    //------------------------------------------------
    // Neural Network
    //------------------------------------------------

    torch::nn::Sequential model{nullptr};

    //------------------------------------------------
    // Network configuration
    //------------------------------------------------

    bool initialized = false;

    uint32_t inputSize = 0;

    uint32_t hiddenSize1 = 0;

    uint32_t hiddenSize2 = 0;
};