#==========================================================
#Script da análise de resultados
#----------------------------------------------------------

print('==========================================================================')
print('Análise descritiva')
print('==========================================================================')

#Leitura de dados
result0 = read.csv("result0.csv", header = FALSE, sep = "\t")
result1 = read.csv("result1.csv", header = FALSE, sep = "\t")
result2 = read.csv("result2.csv", header = FALSE, sep = "\t")
result3 = read.csv("result3.csv", header = FALSE, sep = "\t")

#Tabela descritiva dos resultados
summary(result0)
summary(result1)
summary(result2)
summary(result3)

print('==========================================================================')
print('Teste ANOVA e suas premissas')
print('==========================================================================')

#Preparação da tabela ANOVA
##Cria vetor com a medida UB, no caso V2 (você pode fazer o mesmo com o tempo ou LB)
Medida=c(result0$V2, result1$V2, result2$V2, result3$V2)
##Cada modelo Mi tem 80 réplicas de instâncias
Modelo=c(rep("M0",80), rep("M1",80), rep("M2",55), rep("M3",80))
TabelaMedida=data.frame(Medida, Modelo)
##Salva TabelaMedida em csv
write.table(TabelaMedida, file='arquivo.csv', sep='\t', dec='.', row.names=FALSE)

#Teste de homocedasticidade
library(car)
leveneTest(Medida~Modelo,data=TabelaMedida)

#ANOVA com interação
analise1 <- aov(Medida~Modelo,data=TabelaMedida)
anova(analise1)

##Gráficos relacionados
par(mfrow=c(2,2)) #divide a janela gráfica
plot(analise1)

#Normalidade dos resíduos 
shapiro.test(residuals(analise1))

#Se o teste não satisfaz as premissas de normalidade 
#dos resíduos ou homocedasticidade
print('==========================================================================')
print("Testes não paramétricos: Kruskal Wallis e Welch's ANOVA")
print('==========================================================================')

kruskal.test(Medida~Modelo,data=TabelaMedida)
oneway.test(Medida~Modelo,data=TabelaMedida, na.action=na.omit, var.equal=FALSE) 
## lsmeans pode ser uma outra opção
#model = lm(Medida~Modelo,data=TabelaMedida)
#library(emmeans)
#lsmeans(model, pairwise ~ Modelo, adjust="tukey")

#Gráficos
plot(TabelaMedida$Modelo,TabelaMedida$Medida,xlab="modelo",ylab="UB")
print('==========================================================================')
print("Testes de multiplas comparações com todos os métodos de ajuste de p-valor")
print('==========================================================================')

#Multiplas comparações "holm", "hochberg", "hommel", "bonferroni", "BH", "BY", "fdr", "none"
#https://stat.ethz.ch/R-manual/R-devel/library/stats/html/p.adjust.html
#Este pairwise não é o pareado que necessita de réplicas correlacionadas entre 
#os níveis. Este teste compara os possiveis pares de níveis.
pairwise.wilcox.test(TabelaMedida$Medida,TabelaMedida$Modelo, p.adjust.method = "holm")
pairwise.wilcox.test(TabelaMedida$Medida,TabelaMedida$Modelo, p.adjust.method = "hochberg")
pairwise.wilcox.test(TabelaMedida$Medida,TabelaMedida$Modelo, p.adjust.method = "hommel")
pairwise.wilcox.test(TabelaMedida$Medida,TabelaMedida$Modelo, p.adjust.method = "bonferroni") #reduz a chance de erro tipo 1
pairwise.wilcox.test(TabelaMedida$Medida,TabelaMedida$Modelo, p.adjust.method = "BH")
pairwise.wilcox.test(TabelaMedida$Medida,TabelaMedida$Modelo, p.adjust.method = "BY")
pairwise.wilcox.test(TabelaMedida$Medida,TabelaMedida$Modelo, p.adjust.method = "fdr")
pairwise.wilcox.test(TabelaMedida$Medida,TabelaMedida$Modelo, p.adjust.method = "none")

TukeyHSD(analise1, ordered = TRUE)
