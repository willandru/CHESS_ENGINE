class RLSystem
{
public:

    RLSystem();

    void initialize();

    //------------------------------------------------
    // Inference
    //------------------------------------------------
    bool decide(
        const GameState& state,
        Move& move);

    //------------------------------------------------
    // Learning
    //
    // Called AFTER the selected move has been
    // executed.
    //------------------------------------------------
    void learn(
        const GameState& state,
        const Move& action,
        const GameState& nextState,
        bool checkmate,
        bool lost,
        bool stalemate,
        uint32_t turn);

private:

    //------------------------------------------------
    // Encodes the current state into the neural input.
    //------------------------------------------------
    torch::Tensor encodeState(
        const GameState& state);

    //------------------------------------------------
    // Returns the action index inside the selected
    // candidate vector.
    //------------------------------------------------
    int64_t findActionIndex(
        const Move& move,
        const std::vector<DecisionNode>& candidates);

private:

    DecisionTreeEngine tree;

    std::shared_ptr<DecisionDL> decisionDL;

    std::unique_ptr<RLTrainer> trainer;

    RewardSystem rewardSystem;

    //------------------------------------------------
    // Last inference
    //------------------------------------------------

    std::vector<DecisionNode> lastCandidates;

    torch::Tensor lastState;

    int64_t lastAction = 0;

    uint32_t searchDepth = 1;

    bool initialized = false;
};