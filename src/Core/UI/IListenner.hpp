#ifndef ILISTENNER_HPP
#define ILISTENNER_HPP

#include "../global.hpp"
#include "AWidget.hpp"

class IListenner {
public:
	virtual void	action(GLFWwindow *window, AWidget *src) = 0;
};

#endif