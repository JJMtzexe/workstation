#! Class 1: Creating Data Visualizations using ggplot
library(datasets)
data(mtcars)
head(mtcars)

library(ggplot2)
head(mtcars, 5)

ggplot(aes(x=disp,y=mpg,),data=mtcars)+geom_point()+ggtitle("displacement vs miles per gallon") + labs(x = "Displacement", y = "Miles per Gallon")

mtcars$vs <- as.factor(mtcars$vs)
ggplot(aes(x=vs, y=mpg, fill = vs), data = mtcars) + 
  geom_boxplot(alpha=0.3) +
  theme(legend.position="none")

ggplot(aes(x=wt),data=mtcars) + geom_histogram(binwidth=0.5, fill='black', alpha=0.5)

#! Class 2: Creating Data Visualizations using ggplot