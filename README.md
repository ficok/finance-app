### Introduction:
A terminal-based app for managing personal finance.

### Installation:
1. clone this repository: `git clone https://github.com/ficok/finance-app finance-app`
2. add the folder `finance-app` to path (with this, you will be able to run it from your terminal with just `finance-app`)

### Updating:
- in the `finance-app` folder: `git pull`

### Features:
- adding and spending money
- saving how much money is available
- reserving money:<br>basically allowing for managing savings toward specific items. allows for creating a reservation that has a name, a funding goal and the current funding, so you know how much you need to save and how much you have saved so far toward the item. the funding goal is subtracted from available money, so you don't get tempted to thwart your savings for an impulse purchase.
- logging transactions and printing the log
- logging reservations and changes to reservations and printing the log

### To-do:
- deleting reservations
- subscriptions:<br>will allow for creating a subscription whose price is automatically subtracted from available money every month
- wage:<br>if you have a fixed wage, will allow for automatic monthly adding of the wage to the available money.
- minor bug fixes
- minor code refinement