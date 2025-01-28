###############################
# 1. Load package
###############################
library( ggplot2 )

###############################
# 2. 
###############################
p_caliculate <- read.csv("p_virus_caliculate_differential.csv", header = F)
p_caliculate <- as.data.frame(p_caliculate)
names(p_caliculate) <- c("t", "p")
p_caliculate <- p_caliculate[49401:50001,1:2]

line_size = 1.5
g1 <- ggplot(p_caliculate, aes(x=t))+
  theme_bw()+
  labs(x = "t",y = "p(t)") +
  geom_line(aes(y=p),color="#13AA99", size=line_size)+
  ylim(0,1)

ggsave(file = "p_virus_caliculate_differential.png", plot = g1)
