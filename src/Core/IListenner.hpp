#ifndef ILISTENNER_HPP
#define ILISTENNER_HPP

#include "AWidget.hpp"

class IListenner {
public:
	virtual void	action(AWidget *src) = 0;
};

#endif