#pragma once
#include <iostream>
#include <string>
#include <map>
#include <functional>

class TaskController
{
public:
	TaskController(std::istream& input, std::ostream& output);
	bool HandleUserInput();

private:
	std::istream& m_input;
	std::ostream& m_output;

	using Handler = std::function<void()>;
	using ActionMap = std::map<std::string, Handler>;
	const ActionMap m_actionMap;

	void Info() const;
	void TaskOne() const;
	void TaskTwo() const;
	void TaskThree() const;
	void TaskFour() const;
};
