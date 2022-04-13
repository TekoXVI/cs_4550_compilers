#ifndef DEBUG
#define DEBUG

#define ShowMessages 1 { \
	ShowMessages = 1; \
	if (ShowMessages == 1) { \
		#define MSG(X) (std::cout << X << std::endl;) \
	} \
}

#endif