###############################
# 1. Load package
###############################
library( ggplot2 )

###############################
# 2. Read Data
###############################
data <- read.csv("p_caliculate_direct.csv", header = F)
names(data) <- c("t", "p")
data$p <- data$p/100

t <- list()
lower <- list()
mean <- list()
upper <- list()

variance <- function(x){
  var(x)*(length(x)-1)/length(x) 
  # 標本分散を求める関数を定義
}
###############################
# 3. Mean & Sd
###############################
for (i in 1:11) {
  # i=1
  t <- c(t, (i-1)*0.5)
  st <- (i-1)*100+1
  ft <- i*100
  tdata <- data[st:ft,2]
  N <- length(tdata) 
  tt <- 1.98
  
  # 95%信頼区間の推定
  S <- sqrt(variance(tdata))
  lower <- c(lower, mean(tdata) - tt * S/sqrt(N))
  upper <- c(upper, mean(tdata) + tt * S/sqrt(N))
  mean <- c(mean, mean(tdata))
}
t<-as.data.frame(t)
names(t) <- c("1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11")
lower <- as.data.frame(lower)
names(lower) <- c("1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11")
upper <- as.data.frame(upper)
names(upper) <- c("1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11")
mean <- as.data.frame(mean)
names(mean) <- c("1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11")

hensa <- rbind(t, lower)
hensa <- rbind(hensa, upper)
hensa <- rbind(hensa, mean)
hensa <- t(hensa)
hensa <- as.data.frame(hensa)
names(hensa) <- c("t", "lower", "upper","mean")

# g0 <- 
#   ggplot(hensa, aes(x=t, y=mean))+
#   theme_bw()+
#   geom_errorbar(aes(x=hensa[1,1], ymin=hensa[1,2],ymax=hensa[1,3]),width=.2)+
#   geom_errorbar(aes(x=hensa[2,1], ymin=hensa[2,2],ymax=hensa[2,3]),width=.2)+
#   geom_errorbar(aes(x=hensa[3,1], ymin=hensa[3,2],ymax=hensa[3,3]),width=.2)+
#   geom_errorbar(aes(x=hensa[4,1], ymin=hensa[4,2],ymax=hensa[4,3]),width=.2)+
#   geom_errorbar(aes(x=hensa[5,1], ymin=hensa[5,2],ymax=hensa[5,3]),width=.2)+
#   geom_errorbar(aes(x=hensa[6,1], ymin=hensa[6,2],ymax=hensa[6,3]),width=.2)+
#   geom_errorbar(aes(x=hensa[7,1], ymin=hensa[7,2],ymax=hensa[7,3]),width=.2)+
#   geom_errorbar(aes(x=hensa[8,1], ymin=hensa[8,2],ymax=hensa[8,3]),width=.2)+
#   geom_errorbar(aes(x=hensa[9,1], ymin=hensa[9,2],ymax=hensa[9,3]),width=.2)+
#   geom_errorbar(aes(x=hensa[10,1], ymin=hensa[10,2],ymax=hensa[10,3]),width=.2)+
#   geom_errorbar(aes(x=hensa[11,1], ymin=hensa[11,2],ymax=hensa[11,3]),width=.2)+
#   ylim(0,1)
  
###############################
# 4. differential
###############################
differential <- read.csv("p_caliculate_differential.csv", header = F)
differential <- as.data.frame(differential)
names(differential) <- c("t", "pd")
differential <- differential[50001:49001,]


###############################
# 5. Plot
###############################
# line_size = 1.5
# g1 <- ggplot(differential, aes(x=t))+
#   theme_bw()+
#   labs(x = "t",y = "p(t)") +
#   geom_line(aes(y=pd),color="#13AA99", size=line_size)+
#   ylim(0,1)


g2 <-
  ggplot()+
  theme_bw()+
  layer(
    data=differential, 
    mapping=aes(x=t, y=pd), 
    geom="line", 
    stat="identity", 
    position="identity"
  )+
  layer(
    data=hensa,
    mapping=aes(x=t, ymin=lower,ymax=upper),
    geom="errorbar",
    stat="identity",
    position="identity"
  )
ggsave(file = "p_caliculate_bar.png", plot = g2)

