from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp
from datetime import datetime

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd
# ref: https://github.com/ansible/ansible/pull/17251/files/d132552b6eef805e194d1f30b5d29d4ee6324a58?diff=split&short_path=3e8c7a3
app.jinja_env.filters["add"] = add

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    # get id of active user
    active_user = session["user_id"]

    # query from users the active user info
    user = db.execute("SELECT cash FROM users WHERE id = :userid", userid=active_user)
    c = user[0]["cash"]

    # query from stocks all the rows where user_id == active_user
    rows = db.execute("SELECT symbol, name, date, SUM(shares) FROM stocks WHERE user_id = :userid GROUP BY symbol", userid=active_user)

    # search symbols obtained in the query with lookup and update prices in rows
    for row in rows:
        vals = lookup(row["symbol"])
        row["price"] = vals["price"]
        row["total"] = row["SUM(shares)"]*vals["price"]

    # render index template
    return render_template("index.html", r=rows, cash=c)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""

    # if user reached via POST (as via a form via POST)
    if request.method == "POST":

        # ensure symbol is entered else apology
        if not request.form.get("symbol"):
            return apology("Enter a symbol")

        # ensure shares is entered else apology
        if not request.form.get("shares"):
            return apology("enter number of shares")

        # lookup for symbol
        vals = lookup(request.form.get("symbol"))

        # ensure symbol exist else apology
        if not vals:
            return apology("symbol not valid")

        # get user id
        active_user = session["user_id"]

        # query data of active user
        user = db.execute("SELECT * FROM users WHERE id = :userid", userid=active_user)

        # calculate the cost (shares times price)
        cost = round(int(request.form.get("shares")) * vals["price"], 2)

        # ensure cash is greater than cost
        if user[0]["cash"] < cost:
            return apology("can't afford that cost")

        #substract cost from cash and UPDATE in users
        user_update = db.execute("UPDATE users SET cash = :cash WHERE id = :userid", cash=user[0]["cash"] - cost, userid=active_user)

        # INSERT the data of transaction in stocks (user id, symbol, name, shares, price, date)
        # datetime: https://blog.miguelgrinberg.com/post/the-flask-mega-tutorial-part-xiii-dates-and-times
        new_stock = db.execute("INSERT INTO stocks (symbol, name, shares, price, user_id, date) VALUES(:symbol, :name, :shares, :price, :userid, :now)", symbol=vals["symbol"], name=vals["name"], shares=request.form.get("shares"), price=vals["price"], userid=active_user, now=str(datetime.utcnow()))

        # redirect to index
        return redirect(url_for("index"))

    # else buy reached via GET (as via a link via GET)
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""

    # get id of active user
    active_user = session["user_id"]

    # SELECT from "stocks" all the transactions of the current user
    rows = db.execute("SELECT symbol, shares, price, date  FROM stocks WHERE user_id = :userid ORDER BY date DESC", userid=active_user)

    # render index template
    return render_template("history.html", historial=rows)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure symbol is typed
        if not request.form.get("symbol"):
            return apology("Input a symbol")

        # query and store that symbol in the database
        vals = lookup(request.form.get("symbol"))

        # check if that symbol exist
        if not vals:
            return apology("symbol does not exist")

        # if exist render quoted
        return render_template("quoted.html", symbol=vals["symbol"], name=vals["name"], price=vals["price"])

    # else GET
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    # forget any user_id
    session.clear()

    # if user reached via POST (as via a form via POST)
    if request.method == "POST":

        # ensure username is not empty
        if not request.form.get("username"):
            return apology("a username is necessary")

        # ensure password is not empty
        if not request.form.get("password"):
            return apology("a password is necessary")

        # ensure confirmation is not empty
        if not request.form.get("confirmation"):
            return apology("Type your password again")

        # ensure username is avalaibable - query in database
        checkname = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        if len(checkname) > 0:
            return apology("username already taken")

        # ensure password and confirmation are identical
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("password does not match")

        # insert username and password (hashed) - :new will just get the primary key value and not the whole row, remember that!
        new = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hashed)", username=request.form.get("username"), hashed=pwd_context.hash(request.form.get("password")))
        if not new:
            return apology("Couldn't create username")

        # pull the whole row recently created in new
        rows = db.execute("SELECT * FROM users WHERE id = :userid", userid=new)

        # automatic login
        session["user_id"] = rows[0]["id"]

        # redirect to index
        return redirect(url_for("index"))

    # else user reached via GET (as via a link via GET)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    # if user reach via POST (as via a form via a POST)
    if request.method == "POST":

        # get id of active user
        active_user = session["user_id"]

        # ensure a symbol was submited else apology
        if not request.form.get("symbol"):
            return apology("select a symbol")

        # ensure a share was submited else apology
        if not request.form.get("shares"):
            return apology("missing number of shares")

        # query from users the active user info
        user = db.execute("SELECT * FROM users WHERE id = :userid", userid=active_user)

        # query from stocks all the rows where user_id == active_user
        stock = db.execute("SELECT symbol, SUM(shares) FROM stocks WHERE symbol = :symbol AND user_id = :userid GROUP BY symbol",
        symbol=request.form.get("symbol"), userid=active_user)

        # lookup for updated values fo symbol
        vals = lookup(request.form.get("symbol"))

        # ensure shares does not exceeds current shares else apology
        if int(stock[0]["SUM(shares)"]) < int(request.form.get("shares")):
            return apology("not enough shares in your pocket")

        # INSERT that transaction in the database STOCKS
        sell = db.execute("INSERT INTO stocks (symbol, name, shares, price, user_id, date) VALUES(:symbol, :name, :shares, :price, :userid, :date)", symbol=request.form.get("symbol"), name=vals["name"], shares=0-int(request.form.get("shares")), price=vals["price"], userid=active_user, date=str(datetime.utcnow()))
        # UPDATE USERS
        renew = db.execute("UPDATE users SET cash = :cash WHERE id = :userid", cash=user[0]["cash"]+int(request.form.get("shares"))*vals["price"], userid=active_user)

        # redirect to index
        return redirect(url_for("index"))

    # else user reached via GET (as via a link via GET)
    else:
        # get id of active user
        active_user = session["user_id"]

        # query for how the different symbols given the user
        stock = db.execute("SELECT symbol, SUM(shares) FROM stocks WHERE user_id = :userid GROUP BY symbol", userid=active_user)

        # render sell
        return render_template("sell.html", symbols=stock)

@app.route("/settings", methods=["GET", "POST"])
@login_required
def settings():
    """ change some values"""
    # render settings template
    return render_template("settings.html")

@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """change the current password"""

    # if reached via POST (as via a form)
    if request.method == "POST":

        # get id of active user
        active_user = session["user_id"]

        # ensure password check is not empty else paology
        if not request.form.get("current-password"):
            return apology("type your current password")

        # ensure new password is not empty else apology
        if not request.form.get("new-password"):
            return apology("type your new password")

        # ensure new password confirmation is not empty else apology
        if not request.form.get("new-pass-confirmation"):
            return apology("type your new password again")

        # query for current password
        current = db.execute("SELECT hash FROM users WHERE id = :userid", userid=active_user)

        # check current password is correct
        if not pwd_context.verify(request.form.get("current-password"), current[0]["hash"]):
            return apology("current password wrong")

        # check new password match
        if request.form.get("new-password") != request.form.get("new-pass-confirmation"):
            return apology("new password does not match")

        # Update new password in the database
        renew = db.execute("UPDATE users SET hash = :newhash WHERE id = :userid", newhash=pwd_context.hash(request.form.get("new-password")), userid=active_user)

        # redirect to index
        return redirect(url_for("index"))

    # else reached via GET (as via a link)
    else:
        return render_template("change_password.html")

@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """add more cash"""

    # if reached via POST (as via a form)
    if request.method == "POST":

        # get id of active user
        active_user = session["user_id"]

        # ensure a quantity was entered else apology
        if not request.form.get("new-cash"):
            return apology("Enter a quantity")

        # UPDATE cash in "users" adding the the cash entered to the current cash
        row = db.execute("SELECT cash FROM users WHERE id = :userid", userid=active_user)
        renew = db.execute("UPDATE users SET cash = :cash WHERE id = :userid", cash=int(request.form.get("new-cash"))+row[0]["cash"], userid=active_user)

        updated_cash = db.execute("SELECT cash FROM users WHERE id = :userid", userid=active_user)

        #redirect to new_cash BUG: when udate this page add money
        #return render_template("new_cash.html", old_cash=row[0]["cash"], new_cash=updated_cash[0]["cash"], added_cash=request.form.get("new-cash"))

        # redirect to index
        return redirect(url_for("index"))

    # else reached via GET (as via a link)
    else:
        # render add_cash
        return render_template("add_cash.html")
