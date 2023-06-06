import operator
with open('ciphertext.txt', 'r') as file:
	words = file.read().split()
	dic = {}
	for word in words:
		if len(word) == 2:
			if not word in dic :
				dic[word] = 0
			else:
				dic[word] += 1
	sorted_dic = sorted(dic.items(), key=lambda kv:kv[1])
	print(sorted_dic)
