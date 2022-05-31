

# Hopscotch with AI(땅따먹기) 

### 게임의 프로세스

```
플레이 난이도 입력
유저 정보, 맵 정보 초기화
while(remaining_turs):
	맵과 카드 출력
	for(유저의 카드 사용 횟수):
		유저의 행동(attack or upgrade)
	AI의 행동(attack or upgrade)
승패 판별
```



### 맵의 시각적 구현

![image-20220531130952651](C:\Users\JungHwan\AppData\Roaming\Typora\typora-user-images\image-20220531130952651.png)



- 맵 구현: 이차원 정적 배열의 모든 인덱스에 공백문자를 할당 한뒤 영토의 테두리나 간선 등 문자들을 '덮어 씌우는' 방식으로 맵의 인덱스를 할당

- 24개의 영토 중 최초 4개의 영토가 중립 영토로 할당되고, 남은 영토는 플레이어에게 임의로 배정

- 매 판마다 배정되는 영토가 달라지기 때문에 전략적으로 다른 선택이 요구됨 

- 각 영토는 상하좌우 영토와 인접 

- 플레이어는 자신의 수도(capital)와 연결된 영토에서만 상대방 영토를 공격할 수 있음 

  *어떤 영토가 수도 노드와 연결되어 있는지 파악하기 위해 수도와 연결된 영토가 자기 소유의 영토일 경우 스택에 쌓고 스택이 빌 때까지 union & find 알고리즘 수행* 









### AI의 행동

- 이기고 있을 때는 방어적인 자세를, 지고 있을 때는 공격적인 자세를 취함

- 최적의 공격루트 선택

- 자신이 공격할 수 있는 모든 루트를 탐색

- 해당 루트에서 상대방 영토를 점령했을 때 달라지는 유효 영토의 수를 구해 최대가 될 때의 공격 루트를 선택

- 결과적으로 상대방의 영토를 끊거나 자신의 영토를 연결하는 최적의 Articulation Point(단절점)을 찾아서 공격하게 됨

  

![image-20220531131152130](C:\Users\JungHwan\AppData\Roaming\Typora\typora-user-images\image-20220531131152130.png)







__공격시 AI의 공격 영토 선택 알고리즘__

![image-20220531131024366](C:\Users\JungHwan\AppData\Roaming\Typora\typora-user-images\image-20220531131024366.png)





**방어력 강화시 AI의 영토 선택 알고리즘**

![image-20220531131028699](C:\Users\JungHwan\AppData\Roaming\Typora\typora-user-images\image-20220531131028699.png)









### 승패판정



- 일정한 턴을 다 돌거나 플레이어가 상대의 수도 영토를 점령한 경우 게임 종료
- 유저 승리시  난이도에 비례하는 보상(돈)을 획득,  이 돈으로 자신의 카드를 업그레이드

![image-20220531131315030](C:\Users\JungHwan\AppData\Roaming\Typora\typora-user-images\image-20220531131315030.png)







**담당 기능: 맵 구현 및 전투 함수 구현**







