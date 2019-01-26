#include <iostream>
#include <string>
#include <stdio.h>

#define NUMBER_GENERATIONS  1000

typedef enum _Element
{
    Empty = 0,
    Prey = 1,
    Predator = 2
} Element;

#define N_GRID  50

//////////////////// globals variables ////////////////////

Element gGrid[N_GRID][N_GRID];
double gPreyDeathRate;          // between 0 and 1
double gPredatorDeathRate;      // between 0 and 1
double gPredatorBirthRate;      // between 0 and 1

///////////////////////////////////////////////////////////

static void InitGrid()
{
    //
    // TODO: init with initial configuration (hardcoded or read from file)
    //
    for (int i = 0; i < N_GRID; i++)
    {
        for (int j = 0; j < N_GRID; j++)
        {
            gGrid[i][j] = Empty;
        }
    }

    gPreyDeathRate = 0.0;
    gPredatorDeathRate = 0.0;
    gPredatorBirthRate = 0.0;
}

static void RunOneGeneration()
{
    //
    //  TODO: apply the 3 rules on gGrid (the "live" function)
    //
}

static FILE* InitMovieFile(std::string Filename)
{
    return fopen(Filename.c_str(), "wb");
}

static FILE* InitStatisticsFile(std::string Filename)
{
    return fopen(Filename.c_str(), "w");
}

static void WriteCmovie(FILE *MovieFile, int t)
{
    //
    // TODO: implement this function
    //
}

static void WriteInStatisticsFile(FILE *StatisticsFile)
{
    //
    // TODO: write a line with N_predators, N_preys
    // this function is called at each iteration
    //
}

int main()
{
    std::cout << "Predator-Prey CA" << std::endl;

    InitGrid();
    FILE *movieFile = InitMovieFile("movie.mvi");
    FILE *statisticsFile = InitStatisticsFile("stats.txt");

    for (int t = 0; t < NUMBER_GENERATIONS; t++)
    {
        RunOneGeneration();
        WriteCmovie(movieFile, t);
        WriteInStatisticsFile(statisticsFile);
    }

    if (movieFile)
    {
        fclose(movieFile);
    }

    if (statisticsFile)
    {
        fclose(statisticsFile);
    }

    return 0;
}