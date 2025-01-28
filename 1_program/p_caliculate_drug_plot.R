###############################
# 1. Load package
###############################
library( ggplot2 )

###############################
# 2. Load Data & Plot
###############################
drug <- read.csv("p_caliculate_differential_drug.csv", header = F)
drug <- as.data.frame(drug)
names(drug) <- c("t", "pd")
drug <- drug[49001:50001, 1:2] 

line_size = 1.5
g1 <- ggplot(drug, aes(x=t))+
  theme_bw()+
  labs(x = "t",y = "p(t)") +
  geom_line(aes(y=pd),color="#13AA99", size=line_size)+
  ylim(0,1)

ggsave(file = "p_caliculate_differential_drug.png", plot = g1)

