###############################
# 1. Load package
###############################
library( ggplot2 )

###############################
# 2. Load data
###############################
parameter <- c("lambda", "d", "b", "a")

for (i in 1:4) {
  x_caliculate <- read.csv(paste("x_caliculate_",parameter[i],".csv",sep=""), header = F)
  x_caliculate <- as.data.frame(x_caliculate)
  
  t <- as.data.frame(x_caliculate[1:10001,1])
  x1 <- as.data.frame(log10(x_caliculate[1:10001,2]))
  x2 <- as.data.frame(log10(x_caliculate[10002:20002,2]))
  x3 <- as.data.frame(log10(x_caliculate[20003:30003,2]))
  x4 <- as.data.frame(log10(x_caliculate[30004:40004,2]))
  x5 <- as.data.frame(log10(x_caliculate[40005:50005,2]))
  
  data <- cbind(t, x1)
  data <- cbind(data, x2)
  data <- cbind(data, x3)
  data <- cbind(data, x4)
  data <- cbind(data, x5)
  
  data <- data[1:401,1:6]
  
  names(data) <- c("t", "x1", "x2", "x3", "x4","x5")
  
  line_size = 1.5
  g <- ggplot(data, aes(x=t))+
    theme_bw()+
    labs(x = "t",y = "x(t)") +
    geom_line(aes(y=x1),color="#ccc6cc", size=line_size)+
    geom_line(aes(y=x2),color="#b495cc", size=line_size)+
    geom_line(aes(y=x3),color="#0071bc", size=line_size)+
    geom_line(aes(y=x4),color="#ffa7e2", size=line_size)+
    geom_line(aes(y=x5),color="#f16ba6", size=line_size)+
    # scale_y_log10()+
    # coord_fixed(ratio=1.5)+
    ylim(3, 5)
  
  ggsave(file = paste("x_caliculate_",parameter[i],".png",sep=""), plot = g)
}
