#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>
#include <vector>

static std::map<std::string, int> createGraph(std::stack<std::tuple<std::string,
    int, std::vector<std::string>>> schedule)
{
        std::map<std::string, int> taskValue;

        while (!schedule.empty()) {
            taskValue[std::get<0>(schedule.top())] = std::get<1>(schedule.top());
            schedule.pop();
        }
        return taskValue;
}

static void displaySchedule(int totalDuration,
    std::stack<std::tuple<std::string, int, std::vector<std::string>>> schedule
    , std::vector<int> timeSchedule)
{
    unsigned long int i(0);
    std::stack<std::tuple<std::string, int, std::vector<std::string>>>
    scheduleTmp(schedule);
    std::map<std::string, int> taskValue = createGraph(schedule);
    int draw(0);
    int mem(0);
    std::tuple<std::string, int, std::vector<std::string>> tmp;
    std::string tmpTaskA;
    std::string tmpTaskB;

    //std::sort(timeSchedule.begin(), timeSchedule.end());
    std::cout << "Total duration of construction: " << totalDuration <<
    " weeks" << std::endl << std::endl;
    while (!schedule.empty() && i < timeSchedule.size()) {
        if (std::get<0>(schedule.top()) != "")
            std::cout << std::get<0>(schedule.top()) << " must begin at t=" <<
        timeSchedule[i] << std::endl;
        schedule.pop();
        i++;
    }
    std::cout << std::endl;
    while (!scheduleTmp.empty()) {
            if (std::get<0>(scheduleTmp.top()) != "") {
            std::cout << std::get<0>(scheduleTmp.top()) << '\t' << "(0)" << '\t';
            draw = 0;
            while (draw < mem) {
                std::cout << " ";
                draw++;
            }
            while (draw < taskValue[std::get<0>(scheduleTmp.top())] + mem) {
                std::cout << "=";
                draw++;
            }
            mem = draw;
            std::cout << std::endl;
        }
        scheduleTmp.pop();
    }
}

static int orderTasks(std::stack<std::tuple<std::string,
    int, std::vector<std::string>>> schedule, std::vector<int> &timeSchedule)
{
    int period = 0;
    std::vector<int> bigTmp(0);
    std::map<std::string, int> taskValue = createGraph(schedule);
    std::map<std::string, int> startSchedule;
    std::vector<int>::iterator elem;
    int totalDuration(0);
    int test;

    while (!schedule.empty()) {
        if (std::get<2>(schedule.top()).empty()) {
            startSchedule[std::get<0>(schedule.top())] = 0;
        } else {
            for (auto &i : std::get<2>(schedule.top())) {
                period =
                startSchedule[i] + taskValue.at(i);
                bigTmp.push_back(period);
                elem = std::max_element(bigTmp.begin(), bigTmp.end());
                startSchedule[std::get<0>(schedule.top())] = *elem;
                test = taskValue.at(i);
            }
            bigTmp.clear();
        }
        timeSchedule.push_back(period);
        totalDuration = std::get<1>(schedule.top()) + period;
        schedule.pop();
    }
    return totalDuration;
}

void scheduling(std::vector<std::tuple<std::string,
int, std::vector<std::string>>> &tasks)
{
    std::string taskName;
    bool isRight(false);
    std::vector<int> timeSchedule(0);
    std::stack<std::tuple<std::string,
    int, std::vector<std::string>>> schedule;
    int totalDuration(0);

    while (!tasks.empty()) {
        for (auto &i : tasks) {
            taskName = std::get<0>(i);
            isRight = false;
            for (auto &i : tasks) {
                for (auto &j : std::get<2>(i)) {
                    if (taskName == j)
                        isRight = true;
                }
            }
            if (isRight != true) {
                schedule.push(i);
                tasks.erase(std::remove(tasks.begin(), tasks.end(), i), tasks.end());
            }
        }
    }
    totalDuration = orderTasks(schedule, timeSchedule);
    displaySchedule(totalDuration, schedule, timeSchedule);
}
