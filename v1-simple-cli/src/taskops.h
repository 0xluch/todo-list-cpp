#pragma once
#include "task.h"
#include "storage.h"
#include "ui.h"

void addTask();
void update(int& id, char opr);
void updateTitle(int& id);
void updateStatus(int& id);
void deleteTask(int& id);
