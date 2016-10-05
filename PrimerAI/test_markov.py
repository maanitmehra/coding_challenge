import random
words = [('dog', 'jumping'), ('dog','barking'), ('dog','running'),('dog','barking'), ('dog','running'), ('cat', 'mewing'), ('cat', 'mewing'), ('cat','jumping')]

def create_model(words):
	
	model = {}
	for (word1,word2) in words:
		word1_list = model.keys()
		if word1 not in word1_list:
			model.update({word1:{'':0}})
		if word2 not in model[word1].keys():
			model[word1].update({word2:0})
		model[word1][word2]=model[word1][word2]+1
	for word in model.keys():
		count = 1.0*sum(model[word].values())
		for elem in model[word].keys():
			model[word][elem]= model[word][elem]/count
	return model

def argmax(list):
	arg_max=[]
	for idx,elem in enumerate(list):
		if elem == max(list):
			arg_max.append(idx)
		else:
			pass
	return arg_max[random.randint(0,len(arg_max))]

def create_next_word(prev_word, model):
	## Border conditions
	if prev_word not in model.keys():
		return model.keys()[random.randint(0,len(model.keys()))] 
	else:
		l1 = model[prev_word].keys()
		l2 = model[prev_word].values()
		while True:
		   try:
			arg = l1[argmax(l2)]
			break
		   except:
			pass
		return arg 


model = create_model(words)
n = ['dog','cat','cow']
l = len(n)
for i in range(0,20):
	wrd =  n[random.randint(0,l-1)]
	it = 0
	while True and it<5:
	   try:
		print "(%s,%s)"%(wrd,create_next_word (wrd, model))
		break
	   except:
		it = it + 1
		pass
