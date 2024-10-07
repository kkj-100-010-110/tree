NAME		=	main
CXX			=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++17 -pedantic
RM			=	rm -rf
SRCS		=	main.cpp
OBJS		=	$(SRCS:%.cpp=%.o)
all		: $(NAME)
%.o		: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<
$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
clean	:
	$(RM) $(OBJS)
fclean	:	clean
	$(RM) $(NAME)
re		:	fclean all
.PHONY	:	all clean fclean re
