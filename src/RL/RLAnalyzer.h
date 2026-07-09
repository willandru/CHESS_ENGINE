#pragma once

#include <cstdint>
#include <string>
#include <fstream>
#include <filesystem>


//====================================================
// RL MOVE RECORD
//
// One decision performed by the RL agent.
//
// Stored in moves.csv
//
//====================================================

struct RLMoveRecord
{
    //------------------------------------------------
    // Episode information
    //------------------------------------------------

    uint32_t episode = 0;

    uint32_t turn = 0;



    //------------------------------------------------
    // Decision information
    //------------------------------------------------

    uint32_t selectedAction = 0;

    uint32_t candidateCount = 0;



    //------------------------------------------------
    // Neural network information
    //------------------------------------------------

    float qValue = 0.0f;



    //------------------------------------------------
    // Exploration information
    //------------------------------------------------

    float epsilon = 0.0f;

    bool exploration = false;
};



//====================================================
// RL EPISODE RECORD
//
// One completed game.
//
// Stored in episodes.csv
//
//====================================================

struct RLEpisodeRecord
{
    //------------------------------------------------
    // Episode
    //------------------------------------------------

    uint32_t episode = 0;



    //------------------------------------------------
    // Game result
    //------------------------------------------------

    uint32_t turns = 0;

    bool victory = false;



    //------------------------------------------------
    // RL statistics
    //------------------------------------------------

    float reward = 0.0f;

    float loss = 0.0f;

    float epsilon = 0.0f;
};



//====================================================
// RL SUMMARY RECORD
//
// Global training statistics.
//
// Stored in summary.csv
//
//====================================================

struct RLSummaryRecord
{
    //------------------------------------------------
    // Training
    //------------------------------------------------

    uint32_t totalEpisodes = 0;



    //------------------------------------------------
    // Results
    //------------------------------------------------

    uint32_t victories = 0;

    uint32_t defeats = 0;

    uint32_t draws = 0;



    //------------------------------------------------
    // Statistics
    //------------------------------------------------

    float averageReward = 0.0f;

    float averageLoss = 0.0f;

    float winRate = 0.0f;
};



//====================================================
// RL ANALYZER
//
// Responsible only for logging training information.
//
// Does NOT:
// - train neural networks
// - update weights
// - select actions
//
// Used by RLTrainer to generate analysis files.
//
//====================================================

class RLAnalyzer
{

public:

    //------------------------------------------------
    // Constructor
    //------------------------------------------------

    RLAnalyzer();



    //------------------------------------------------
    // Initialize analyzer
    //
    // Creates output folder and CSV files.
    //
    // Example:
    //
    // initialize("player1");
    //
    //------------------------------------------------

    bool initialize(
        const std::string& playerName);



    //------------------------------------------------
    // Record one agent decision
    //
    // File:
    // moves.csv
    //
    //------------------------------------------------

    void recordMove(
        const RLMoveRecord& record);



    //------------------------------------------------
    // Record completed game
    //
    // File:
    // episodes.csv
    //
    //------------------------------------------------

    void recordEpisode(
        const RLEpisodeRecord& record);



    //------------------------------------------------
    // Save final training statistics
    //
    // File:
    // summary.csv
    //
    //------------------------------------------------

    void saveSummary(
        const RLSummaryRecord& record);



    //------------------------------------------------
    // Close CSV files
    //------------------------------------------------

    void shutdown();



    //------------------------------------------------
    // Status
    //------------------------------------------------

    bool isInitialized() const;



private:

    //------------------------------------------------
    // Folder management
    //------------------------------------------------

    bool createFolders();



    //------------------------------------------------
    // Timestamp generation
    //
    // Format:
    //
    // DD-MM_HH-MM
    //
    //------------------------------------------------

    std::string createTimestamp() const;



private:

    //------------------------------------------------
    // Output folder
    //------------------------------------------------

    std::filesystem::path outputFolder;



    //------------------------------------------------
    // CSV streams
    //------------------------------------------------

    std::ofstream moveFile;

    std::ofstream episodeFile;

    std::ofstream summaryFile;



    //------------------------------------------------
    // State
    //------------------------------------------------

    bool initialized = false;

};
