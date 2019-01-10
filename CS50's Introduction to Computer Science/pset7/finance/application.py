import os

from cs50 import SQL, eprint
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Select current user in db
    row = db.execute("SELECT * FROM users WHERE id=:user_id", user_id=session["user_id"])

    # Select user's portfolio from db
    portfolio = db.execute("SELECT symbol, sum(shares) as shares FROM portfolio WHERE user_id=:user_id GROUP BY symbol",
                           user_id=session["user_id"])

    # Dict of quotes
    quotes = {}
    # Total for shares
    total = 0
    for stock in portfolio:
        quotes[stock["symbol"]] = lookup(stock["symbol"])
        total += stock["shares"] * lookup(stock["symbol"])["price"]

    # Remaining cash
    cash = row[0]["cash"]

    return render_template("index.html", cash=cash, total=total, quotes=quotes, portfolio=portfolio)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))

        # Check if symbol is exist
        if quote == None:
            return apology("Unknown symbol", 400)

        # Number of shares to buy
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("shares must be a positive integer", 400)

        # Check if number of shares to buy less or equal to zero
        if shares <= 0:
            return apology("can't buy less than or 0 shares", 400)

        # Check remaining cash to buy needed amount of shares
        row = db.execute("SELECT * FROM users WHERE id = :user_id", user_id=session["user_id"])
        cash = row[0]["cash"]
        price = quote["price"]
        total = price * shares

        if cash < total:
            return apology("not enough cash", 400)

        # Inserting new row to portfolio table of db (shares buying)
        db.execute("INSERT INTO portfolio (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
                   user_id=session["user_id"], symbol=request.form.get("symbol"), shares=shares, price=price)

        # Updating amount of cash in users table of db
        db.execute("UPDATE users SET cash=cash-:total WHERE id=:user_id", total=total, user_id=session["user_id"])

        flash("Bought!")

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Select current user in db
    row = db.execute("SELECT * FROM users WHERE id=:user_id", user_id=session["user_id"])

    # Select user's portfolio from db
    portfolio = db.execute("SELECT * FROM portfolio WHERE user_id=:user_id", user_id=session["user_id"])

    # Dict of quotes
    quotes = {}
    # Total for shares
    total = 0
    for stock in portfolio:
        quotes[stock["symbol"]] = lookup(stock["symbol"])
        total += stock["shares"] * lookup(stock["symbol"])["price"]

    return render_template("history.html", quotes=quotes, portfolio=portfolio)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        # Check if symbol is existed
        if quote == None:
            return apology("Unknown symbol", 400)
        else:
            # Render template with company full name and share price
            return render_template("quoted.html", quote=quote, symbol=symbol)
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("Missing username!", 400)

        # Query database for username
        result = db.execute("SELECT * FROM users WHERE username = :username",
                            username=request.form.get("username"))

        # Ensure username is not already taken
        if result:
            return apology("username is already taken", 400)

        # Ensure password and confirmation were submitted
        if not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide password and confirmation", 400)

        # Ensure password and confirmation match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("password and confirmation do not match", 400)

        # INSERT the new user into db (users table), storing a hash of the user’s password
        hash = generate_password_hash(request.form.get("password"))
        user_id = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                             username=request.form.get("username"), hash=hash)

        # Remember which user has registered
        session["user_id"] = user_id

        # Display a flash message
        flash("Registered!")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """Change password functionality"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure all fields are filled in
        if not request.form.get("current_password") or not request.form.get("new_password") or not request.form.get("confirmation"):
            return apology("all fields are mandatory", 400)

        # Query database for user and hash
        row = db.execute("SELECT * FROM users WHERE id=:user_id", user_id=session["user_id"])

        # Ensure user filled in the right current password
        if not check_password_hash(row[0]["hash"], request.form.get("current_password")):
            return apology("current password is incorrect", 400)

        # Ensure new password and confirmation match
        if request.form.get("new_password") != request.form.get("confirmation"):
            return apology("password and confirmation do not match", 400)

        # UPDATE user's password in db, storing hash
        new_hash = generate_password_hash(request.form.get("new_password"))
        db.execute("UPDATE users SET hash=:new_hash WHERE id=:user_id", user_id=session["user_id"], new_hash=new_hash)

        # Display a flash message
        flash("Password changed!")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("change_password.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        if request.form.get("symbol") == None:
            return apology("Missing symbol", 400)

        # Check number of shares for chosen symbol in db
        portfolio = db.execute("SELECT symbol, sum(shares) as shares FROM portfolio WHERE user_id=:user_id AND symbol=:symbol GROUP BY symbol",
                               user_id=session["user_id"], symbol=request.form.get("symbol"))

        shares = int(request.form.get("shares"))
        price = lookup(request.form.get("symbol"))["price"]
        if shares > portfolio[0]["shares"]:
            return apology("Not enough shares", 400)

        # Total cash for sold shares
        total = shares * price

        # Inserting new row to portfolio table of db (shares sold)
        db.execute("INSERT INTO portfolio (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
                   user_id=session["user_id"], symbol=request.form.get("symbol"), shares=(-1)*shares, price=price)

        # Updating amount of cash in users table of db
        db.execute("UPDATE users SET cash=cash+:total WHERE id=:user_id", total=total, user_id=session["user_id"])

        flash("Sold!")

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # Select user's portfolio from db
        portfolio = db.execute("SELECT symbol, sum(shares) as shares FROM portfolio WHERE user_id=:user_id GROUP BY symbol",
                               user_id=session["user_id"])
        return render_template("sell.html", portfolio=portfolio)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
