# we got to do this for each variant like its a diffrent data set every time ref jpeg  

# make a dictionary where you have the probabilities of infection and the diffrent covid variants  

# vaccine, probability of infection rate  
from logging import exception
Omicron = { 
        "Astrazeneca":0.36, 
        "CanSino":0.32, 
        "CoronaVac":0.24, 
        "Covaxin":0.38, 
        "JohnsonJohnson":0.33,
        "Moderna":0.48, 
        "Novavax":0.43, 
        "Pfizer":0.44 ,
        "Other_mrna":0.45 , 
        "SinoPharm":0.35 ,
        "Sputnik_V":0.44 ,
    } 


Normal = {
        "Astrazeneca": 0.63,
        "CanSino": 0.62,
        "CoronaVac": 0.47,
        "Covaxin": 0.73,
        "JohnsonJohnson": 0.72,
        "Moderna": 0.92,
        "Novavax": 0.83,
        "Pfizer": 0.86,
        "Other_mrna": 0.45,
        "SinoPharm": 0.68,
        "Sputnik_V": 0.86,
    } 

Delta= {
        "Astrazeneca": 0.69,
        "CanSino": 0.61,
        "CoronaVac": 0.46,
        "Covaxin": 0.72,
        "JohnsonJohnson": 0.64,
        "Moderna": 0.91,
        "Novavax": 0.82,
        "Pfizer": 0.84,
        "Other_mrna": 0.85,
        "SinoPharm": 0.67,
        "Sputnik_V": 0.85,
    }

user_input = input("Type a vaccine in here") 
user_input1 = Delta
print(user_input1[user_input]) 

