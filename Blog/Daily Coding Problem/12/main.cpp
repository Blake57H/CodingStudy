#include <iostream>
#include <memory>
#include <vector>

struct Step
{
    // public:
    unsigned int currentHeight;
    unsigned int stepReadyToTake;
    std::vector<std::shared_ptr<Step>> nextSteps;

    Step(unsigned int currentHeight, unsigned int stepReadyToTake)
    {
        this->currentHeight = currentHeight;
        this->stepReadyToTake = stepReadyToTake;
    }
};

void buildStepsRecursive(std::shared_ptr<Step> step, const std::vector<unsigned int> &availableSteps, const unsigned int &totalHeight)
{
    unsigned int currentHeightAfterStep = step->currentHeight + step->stepReadyToTake;
    if (currentHeightAfterStep >= totalHeight)
        // height is reached (valid) or surpassed (invalid), do not build any more steps
        return;

    unsigned int maxPossibleStep = totalHeight - step->currentHeight;

    for (unsigned int stepCandidate : availableSteps)
    {
        if (stepCandidate > maxPossibleStep)
            continue;
        step->nextSteps.push_back(std::make_shared<Step>(Step(currentHeightAfterStep, stepCandidate)));
    }

    for (auto nextStep : step->nextSteps)
    {
        buildStepsRecursive(nextStep, availableSteps, totalHeight);
    }
}

void removeInvalidStepsRecursive(std::shared_ptr<Step> currentStep, unsigned int &totalHeight)
{
    // depth first removal
    // child can't remove itself from parent (without function return), so I'm checking child directly
    for (auto nextStep = currentStep->nextSteps.begin(); nextStep != currentStep->nextSteps.end();)
    {
        if ((*nextStep)->nextSteps.size() > 0)
        {
            // if child can't reach the totalHeight, it will have no child and will be erased in the next if statement
            removeInvalidStepsRecursive(*nextStep, totalHeight);
        }

        // after operation above, nextSteps.size() might be 0, indicating this step cannot reach totalHeight
        if ((*nextStep)->nextSteps.size()==0 && (*nextStep)->currentHeight + (*nextStep)->stepReadyToTake != totalHeight)
        {
            currentStep->nextSteps.erase(nextStep); // erase only if it has no child.
            continue;
        }
        nextStep++;
    }
}

// note: does this function has a lot of data copy? Looks so to me... every time a value return
// all possible steps can be represented by a 2-dimension int array.
std::vector<std::vector<unsigned int>> backtrackValidSteps(std::shared_ptr<Step> currentStep)
{
    if (currentStep->nextSteps.size() == 0)
        return std::vector<std::vector<unsigned int>>{std::vector<unsigned int>{currentStep->stepReadyToTake}};

    std::vector<std::vector<unsigned int>> result;
    for (auto nextStep : currentStep->nextSteps)
    {
        for (auto nextStepReadyToTake : backtrackValidSteps(nextStep))
        {
            nextStepReadyToTake.insert(nextStepReadyToTake.begin(), currentStep->stepReadyToTake);
            result.push_back(nextStepReadyToTake);
        }
    }
    return result;
}

int solve(std::vector<unsigned int> availableSteps, unsigned int totalHeight)
{
    std::vector<std::shared_ptr<Step>> firstSteps; // root node
    std::vector<std::vector<unsigned int>> uniqueWays;
    for (unsigned int &availableStep : availableSteps)
    {
        firstSteps.push_back(std::make_shared<Step>(Step(0U, availableStep)));
        buildStepsRecursive(firstSteps.back(), availableSteps, totalHeight);
        removeInvalidStepsRecursive(firstSteps.back(), totalHeight);
        // removeInvalidStepsRecursive does not check root node. checking it now.
        if(firstSteps.back()->nextSteps.size()==0 && firstSteps.back()->stepReadyToTake != totalHeight)
            firstSteps.pop_back();
    }

    for (auto &steps : firstSteps)
    {
        for (auto &uniqueWay : backtrackValidSteps(steps))
        {
            uniqueWays.push_back(uniqueWay);
        }
    }

    for (auto &uniqueWay : uniqueWays)
    {
        for (auto& step : uniqueWay){
            std::cout << step << ", ";
        }
        std::cout << std::endl;
    }
    return uniqueWays.size();
}

int main(int argc, char *argv[])
{
    std::vector<unsigned int> availableSteps1{1, 2};
    unsigned int N1 = 4;
    auto result = solve(availableSteps1, N1);
    std::cout << "Result: " << result << "\n";

    std::vector<unsigned int> availableSteps2{3, 5}, availableSteps3{1, 3, 5};
    unsigned int N2 = 6;
    result = solve(availableSteps2, N2);
    std::cout << "Result: " << result << "\n";  // expects 1 (3+3)
    result = solve(availableSteps3, N2);
    std::cout << "Result: " << result << "\n";

    return 0;
}