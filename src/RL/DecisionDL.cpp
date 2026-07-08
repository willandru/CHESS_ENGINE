#include "DecisionDL.h"

#include <algorithm>
#include <iostream>
#include <random>


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
    uint32_t hiddenSize,
    uint32_t outputSize)
{
    std::cout
        << "[DecisionDL] initialize()"
        << std::endl;

    inputSize = inputSize_;

    std::cout
        << "[DecisionDL] Input: "
        << inputSize
        << std::endl;

    std::cout
        << "[DecisionDL] Hidden: "
        << hiddenSize
        << std::endl;

    std::cout
        << "[DecisionDL] Output: "
        << outputSize
        << std::endl;



    //------------------------------------------------
    // Create network
    //------------------------------------------------

    std::cout
        << "[DecisionDL] Creating Sequential..."
        << std::endl;

    model =
        torch::nn::Sequential(

            torch::nn::Linear(
                inputSize,
                hiddenSize
            ),

            torch::nn::ReLU(),

            torch::nn::Linear(
                hiddenSize,
                hiddenSize
            ),

            torch::nn::ReLU(),

            torch::nn::Linear(
                hiddenSize,
                outputSize
            )

        );

    std::cout
        << "[DecisionDL] Sequential created"
        << std::endl;



    //------------------------------------------------
    // Register module
    //------------------------------------------------

    std::cout
        << "[DecisionDL] Registering module..."
        << std::endl;

    register_module(
        "model",
        model
    );

    std::cout
        << "[DecisionDL] Module registered"
        << std::endl;



    //------------------------------------------------
    // Verify network
    //------------------------------------------------

    std::cout
        << "[DecisionDL] Number of layers: "
        << model->size()
        << std::endl;

    std::cout
        << "[DecisionDL] initialize() finished"
        << std::endl;
}

//====================================================
// FORWARD
//====================================================

torch::Tensor DecisionDL::forward(
    torch::Tensor input)
{
    std::cout
        << "[DecisionDL] forward()"
        << std::endl;

    std::cout
        << "[DecisionDL] Input shape: "
        << input.sizes()
        << std::endl;

    std::cout
        << "[DecisionDL] Input dtype: "
        << input.dtype()
        << std::endl;

    std::cout
        << "[DecisionDL] Input device: "
        << input.device()
        << std::endl;

    std::cout
        << "[DecisionDL] Input tensor:"
        << std::endl;

    std::cout
        << input
        << std::endl;



    std::cout
        << "[DecisionDL] Executing model->forward()..."
        << std::endl;

    torch::Tensor output =
        model->forward(input);

    std::cout
        << "[DecisionDL] Forward finished"
        << std::endl;

    std::cout
        << "[DecisionDL] Output:"
        << std::endl;

    std::cout
        << output
        << std::endl;

    return output;
}


//====================================================
// ENCODE CHILDREN
//
// Output:
//
// [1,10]
//
//====================================================

torch::Tensor DecisionDL::encodeChildren(
    const std::vector<DecisionNode>& children)
{

    std::vector<float> values;

    values.reserve(
        MAX_CHILDREN
    );



    for(uint32_t i = 0;
        i < MAX_CHILDREN;
        i++)
    {

        if(i < children.size())
        {
            values.push_back(
                encodeNode(
                    children[i]
                )
            );
        }
        else
        {
            values.push_back(
                0.0f
            );
        }

    }



    torch::Tensor tensor =
        torch::tensor(
            values,
            torch::kFloat32
        );


    return tensor.unsqueeze(0);

}



//====================================================
// ENCODE NODE
//====================================================

float DecisionDL::encodeNode(
    const DecisionNode& node)
{

    return node.evaluation;

}



//====================================================
// RANDOM CHILD SELECTION
//====================================================

std::vector<DecisionNode>
DecisionDL::selectChildren(
    const std::vector<DecisionNode>& children)
{

    std::vector<DecisionNode> selected;


    if(children.empty())
        return selected;



    //------------------------------------------------
    // Copy all children
    //------------------------------------------------

    selected = children;



    //------------------------------------------------
    // Shuffle randomly
    //------------------------------------------------

    std::shuffle(
        selected.begin(),
        selected.end(),
        std::mt19937{
            std::random_device{}()
        }
    );



    //------------------------------------------------
    // Keep maximum 10
    //------------------------------------------------

    if(selected.size() > MAX_CHILDREN)
    {
        selected.resize(
            MAX_CHILDREN
        );
    }



    std::cout
        << "[DecisionDL] Selected "
        << selected.size()
        << " candidate nodes"
        << std::endl;


    return selected;

}