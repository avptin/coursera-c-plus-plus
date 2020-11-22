
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/f9Art/triekier-zadach

#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

/*
// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};
// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;
*/

class TeamTasks {
 public:
  // Получить статистику по статусам задач конкретного разработчика

  const TasksInfo& GetPersonTasksInfo(const string& person) const {
    return db.at(person);
  }

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person) { ++db[person][TaskStatus::NEW]; }

  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person,
                                                 int task_count) {
    TasksInfo updated_tasks;
    TasksInfo untouched_tasks;
    TasksInfo shadowed_tasks;

    if (db.count(person) == 0) {
      return make_pair(updated_tasks, untouched_tasks);
    }

    db[person][TaskStatus::NEW] += 0;
    db[person][TaskStatus::IN_PROGRESS] += 0;
    db[person][TaskStatus::TESTING] += 0;
    db[person][TaskStatus::DONE] += 0;

    shadowed_tasks = db[person];
    untouched_tasks = db[person];

    int carry = 0;
    for (auto& [key, value] : db[person]) {
      // NEW → IN_PROGRESS → TESTING → DONE
      updated_tasks[key] = carry;
      carry = 0;

      if ((shadowed_tasks[key] != 0) && (task_count != 0) &&
          (key != TaskStatus::DONE)) {
        while ((shadowed_tasks[key] != 0) && (task_count != 0)) {
          --task_count;
          --shadowed_tasks[key];
          ++carry;
        }
        untouched_tasks[key] -= carry;
      }
      shadowed_tasks[key] += updated_tasks[key];
    }

    // Remove DONE from untouched
    untouched_tasks[TaskStatus::DONE] = 0;

    // Erase empty
    for (auto it = updated_tasks.cbegin(), next_it = it;
         it != updated_tasks.cend(); it = next_it) {
      ++next_it;
      if (it->second == 0) {
        updated_tasks.erase(it);
      }
    }

    for (auto it = untouched_tasks.cbegin(), next_it = it;
         it != untouched_tasks.cend(); it = next_it) {
      ++next_it;
      if (it->second == 0) {
        untouched_tasks.erase(it);
      }
    }

    for (auto it = shadowed_tasks.cbegin(), next_it = it;
         it != shadowed_tasks.cend(); it = next_it) {
      ++next_it;
      if (it->second == 0) {
        shadowed_tasks.erase(it);
      }
    }

    // Update main data
    db[person] = shadowed_tasks;

    return make_pair(updated_tasks, untouched_tasks);
  }

 private:
  map<string, TasksInfo> db;
};
