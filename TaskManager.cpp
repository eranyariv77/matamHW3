#include "TaskManager.h"
#include <stdexcept>

const int TaskManager::findPerson(const string &personName) const {
    int i = 0;
    for(; i < MAX_PERSONS; ++i){
        if(persons[i].getName() == personName){
            return i;
        }
    }
    return NOT_FOUND;
}

const int TaskManager::getLength()const{
    int i = 0;
    for(; i < MAX_PERSONS; ++i){
        if(persons[i].getName() == ""){
        break;
        }
    }
    return i;
}

void TaskManager::assignTask(const string &personName, const Task &task){
    if(findPerson(personName) != NOT_FOUND){
        persons[findPerson(personName)].assignTask(task);
    }else{
        if(getLength() >= MAX_PERSONS){
            throw std::runtime_error("Maximum number of persons reached");
        }
        Person newPerson(personName);
        newPerson.assignTask(task);
        persons[getLength()] = newPerson;
    }
    allTasks.insert(task);
}

void TaskManager::completeTask(const string &personName){
    if(findPerson(personName) != NOT_FOUND){
        int taskId = persons[findPerson(personName)].completeTask();
        for(SortedList<Task>::ConstIterator it = allTasks.begin(); it != allTasks.end(); ++it){
            if((*it).getId() == taskId){
                allTasks.remove(it);
                break;
            }
        }
    }
}



void TaskManager::bumpPriorityByType(TaskType type, int priority){
    if(priority > 0){
        for(int i = 0; i < getLength(); i++){
            SortedList<Task> oldTasks = persons[i].getTasks();
            SortedList<Task> newTasks;
            for(SortedList<Task>::ConstIterator it = oldTasks.begin(); it != oldTasks.end(); ++it){
                Task task = *it;
                if (task.getType() == type){
                    for(SortedList<Task>::ConstIterator itTasks = allTasks.begin();
                     itTasks != allTasks.end(); ++itTasks){
                        if((*itTasks).getId() == task.getId()){
                            allTasks.remove(itTasks);
                            break;
                        } 
                    }
                    Task bumpedTask(task.getPriority() + priority, type,task.getDescription());
                    bumpedTask.setId(task.getId());
                    newTasks.insert(bumpedTask);
                    allTasks.insert(bumpedTask);
                }else{
                    newTasks.insert(task);
                }
            }
            persons[i].setTasks(newTasks);
        }
    }
}

void TaskManager::printAllEmployees() const{
    for(int i = 0; i < getLength(); i++){
        std::cout << persons[i] << "\n" << std::endl;
    }
}

void TaskManager::printAllTasks() const{
    for(SortedList<Task>::ConstIterator it = allTasks.begin(); it != allTasks.end(); ++it){
        std::cout << *it << "\n" << std::endl;
    }
}

void TaskManager::printTasksByType(TaskType type) const{
    for(SortedList<Task>::ConstIterator it = allTasks.begin(); it != allTasks.end(); ++it){
        if((*it).getType() == type){
        std::cout << *it << "\n" << std::endl;
        }
    }
}
