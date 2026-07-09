#include "RLAnalyzer.h"

#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>


//====================================================
// CONSTRUCTOR
//====================================================

RLAnalyzer::RLAnalyzer()
{
}



//====================================================
// INITIALIZE ANALYZER
//====================================================

bool RLAnalyzer::initialize(
    const std::string& playerName)
{

    outputFolder =
        std::filesystem::path(
            "src/RL/results") /
        playerName /
        createTimestamp();



    if(!createFolders())
        return false;



    //------------------------------------------------
    // Open CSV files
    //------------------------------------------------

    moveFile.open(
        outputFolder / "moves.csv",
        std::ios::out);



    episodeFile.open(
        outputFolder / "episodes.csv",
        std::ios::out);



    summaryFile.open(
        outputFolder / "summary.csv",
        std::ios::out);



    if(!moveFile.is_open() ||
       !episodeFile.is_open() ||
       !summaryFile.is_open())
    {
        shutdown();
        return false;
    }



    //------------------------------------------------
    // CSV headers
    //------------------------------------------------

    moveFile
        << "Episode,"
        << "Turn,"
        << "SelectedAction,"
        << "CandidateCount,"
        << "QValue,"
        << "Epsilon,"
        << "Exploration"
        << "\n";



    episodeFile
        << "Episode,"
        << "Turns,"
        << "Victory,"
        << "Reward,"
        << "Loss,"
        << "Epsilon"
        << "\n";



    summaryFile
        << "TotalEpisodes,"
        << "Victories,"
        << "Defeats,"
        << "Draws,"
        << "AverageReward,"
        << "AverageLoss,"
        << "WinRate"
        << "\n";



    initialized = true;



    return true;

}



//====================================================
// RECORD MOVE
//====================================================

void RLAnalyzer::recordMove(
    const RLMoveRecord& record)
{

    if(!initialized)
        return;



    moveFile
        << record.episode << ","
        << record.turn << ","
        << record.selectedAction << ","
        << record.candidateCount << ","
        << record.qValue << ","
        << record.epsilon << ","
        << (record.exploration ? 1 : 0)
        << "\n";

}



//====================================================
// RECORD EPISODE
//====================================================

void RLAnalyzer::recordEpisode(
    const RLEpisodeRecord& record)
{

    if(!initialized)
        return;



    episodeFile
        << record.episode << ","
        << record.turns << ","
        << (record.victory ? 1 : 0) << ","
        << record.reward << ","
        << record.loss << ","
        << record.epsilon
        << "\n";

}



//====================================================
// SAVE SUMMARY
//====================================================

void RLAnalyzer::saveSummary(
    const RLSummaryRecord& record)
{

    if(!initialized)
        return;



    summaryFile
        << record.totalEpisodes << ","
        << record.victories << ","
        << record.defeats << ","
        << record.draws << ","
        << record.averageReward << ","
        << record.averageLoss << ","
        << record.winRate
        << "\n";

}



//====================================================
// SHUTDOWN
//====================================================

void RLAnalyzer::shutdown()
{

    if(moveFile.is_open())
        moveFile.close();



    if(episodeFile.is_open())
        episodeFile.close();



    if(summaryFile.is_open())
        summaryFile.close();



    initialized = false;

}



//====================================================
// IS INITIALIZED
//====================================================

bool RLAnalyzer::isInitialized() const
{
    return initialized;
}



//====================================================
// CREATE FOLDERS
//====================================================

bool RLAnalyzer::createFolders()
{

    try
    {
        std::filesystem::create_directories(
            outputFolder);
    }
    catch(...)
    {
        return false;
    }



    return true;

}



//====================================================
// CREATE TIMESTAMP
//
// Format:
//
// DD-MM_HH-MM
//
//====================================================

std::string RLAnalyzer::createTimestamp() const
{

    auto now =
        std::chrono::system_clock::now();



    std::time_t time =
        std::chrono::system_clock::to_time_t(now);



    std::tm tm =
        *std::localtime(&time);



    std::ostringstream stream;



    stream
        << std::put_time(
            &tm,
            "%d-%m_%H-%M");



    return stream.str();

}