# -*- coding: utf-8 -*-
"""
Created on Fri May 13 17:31:13 2022

@author: Sush
"""
userName = input("Hello! Welcome to EVote! \n\nUsername: ") 
password = input("Password: ") 

count = 0 
count += 1 


while userName == userName and password == password: 


    if count == 3: 
        print("\nThree Username and Password Attempts used. Goodbye") 
        break 


    elif userName == 'elmo' and password == 'blue': 
        print("Welcome! ")
        break 


    elif userName != 'elmo' and password != 'blue': 
        print("Your Username and Password is wrong!") 
        userName = input("\n\nUsername: ")
        password = input("Password: ") 
        count += 1 
        continue 

    elif userName == 'elmo' and password != 'blue': 
        print("Your Password is wrong!") 
        userName = input("\n\nUsername: ") 
        password = input("Password: ") 
        count += 1 
        continue 


    elif userName != 'elmo' and password == 'blue': 
        print("Your Username is wrong!") 
        userName = input("\n\nUsername: ") 
        password = input("Password: ")
        count += 1 