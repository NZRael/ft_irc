NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++98 -I./inc

SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = main.cpp \
       $(SRCS_DIR)/ACommand.cpp \
       $(SRCS_DIR)/Server.cpp \
       $(SRCS_DIR)/Client.cpp \
       $(SRCS_DIR)/Channel.cpp \
       $(SRCS_DIR)/Join.cpp \
       $(SRCS_DIR)/Nick.cpp \
       $(SRCS_DIR)/Pass.cpp \
       $(SRCS_DIR)/Privmsg.cpp \
       $(SRCS_DIR)/User.cpp \
       $(SRCS_DIR)/Mode.cpp \
       $(SRCS_DIR)/Invite.cpp \
       $(SRCS_DIR)/Kick.cpp \
       $(SRCS_DIR)/Ping.cpp \
       $(SRCS_DIR)/Topic.cpp

OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.cpp=.o)))

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJS_DIR)/main.o: main.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re