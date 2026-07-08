#pragma once

#include <torch/torch.h>

#include <vector>
#include <cstdint>

#include "DecisionNode.h"



class DecisionDL : public torch::nn::Module
{

public:


    static constexpr uint32_t MAX_CHILDREN = 10;



public:


    DecisionDL();



    void initialize(
        uint32_t inputSize,
        uint32_t hiddenSize,
        uint32_t outputSize);



    torch::Tensor forward(
        torch::Tensor input);



    //------------------------------------------------
    // Encode selected children
    //
    // Output:
    //
    // [1,10]
    //
    //------------------------------------------------

    torch::Tensor encodeChildren(
        const std::vector<DecisionNode>& children);



    //------------------------------------------------
    // Select random children
    //
    // Input:
    // all children from current state
    //
    // Output:
    // maximum 10 random children
    //
    //------------------------------------------------

    std::vector<DecisionNode> selectChildren(
        const std::vector<DecisionNode>& children);



private:


    float encodeNode(
        const DecisionNode& node);



private:


    torch::nn::Sequential model{nullptr};


    uint32_t inputSize = MAX_CHILDREN;

};