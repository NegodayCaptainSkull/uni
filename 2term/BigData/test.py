from tkinter import *
import random

SEG_SIZE = 20
WIDTH = 500
HEIGHT = 500
IN_GAME = True
SPEED = 100


# ─── Еда ────────────────────────────────────────────
def create_food():
    global food
    x = SEG_SIZE * random.randint(0, (WIDTH // SEG_SIZE) - 1)
    y = SEG_SIZE * random.randint(0, (HEIGHT // SEG_SIZE) - 1)
    food = c.create_oval(x, y, x + SEG_SIZE, y + SEG_SIZE,
                         fill="red", outline="white")


def check_food():
    global food
    head = c.coords(s.segments[-1].instance)
    f = c.coords(food)
    if head[0] == f[0] and head[1] == f[1]:
        s.add_segment()
        c.delete(food)
        create_food()


# ─── Столкновения ───────────────────────────────────
def check_collision():
    global IN_GAME
    x1, y1, x2, y2 = c.coords(s.segments[-1].instance)
    # Стены
    if x1 < 0 or x2 > WIDTH or y1 < 0 or y2 > HEIGHT:
        IN_GAME = False
    # Сам в себя
    head = c.coords(s.segments[-1].instance)
    for i in range(len(s.segments) - 1):
        if c.coords(s.segments[i].instance) == head:
            IN_GAME = False


# ─── Игровой цикл ───────────────────────────────────
def game_loop():
    if IN_GAME:
        s.move()
        check_food()
        check_collision()
        root.after(SPEED, game_loop)
    else:
        c.create_text(WIDTH / 2, HEIGHT / 2,
                      text="Game Over!", font=("Arial", 30), fill="red")


# ─── Сегмент змейки ─────────────────────────────────
class Segment(object):
    def __init__(self, x, y):
        self.instance = c.create_rectangle(
            x, y, x + SEG_SIZE, y + SEG_SIZE,
            fill="green", outline="white"
        )


# ─── Змейка ─────────────────────────────────────────
class Snake(object):
    def __init__(self, segments):
        self.segments = segments
        self.mapping = {
            "Down": (0, 1), "Up": (0, -1),
            "Left": (-1, 0), "Right": (1, 0)
        }
        self.vector = self.mapping["Right"]

    def move(self):
        # Каждый сегмент занимает позицию следующего
        for index in range(len(self.segments) - 1):
            segment = self.segments[index].instance
            x1, y1, x2, y2 = c.coords(self.segments[index + 1].instance)
            c.coords(segment, x1, y1, x2, y2)

        # Голова (последний сегмент!) двигается вперёд
        x1, y1, x2, y2 = c.coords(self.segments[-2].instance)
        c.coords(self.segments[-1].instance,               # ← было -2, нужно -1
                 x1 + self.vector[0] * SEG_SIZE,
                 y1 + self.vector[1] * SEG_SIZE,
                 x2 + self.vector[0] * SEG_SIZE,
                 y2 + self.vector[1] * SEG_SIZE)

    def change_direction(self, event):
        if event.keysym in self.mapping:
            new = self.mapping[event.keysym]
            # Запрет разворота на 180°
            if (new[0] * -1, new[1] * -1) != self.vector:
                self.vector = new

    def add_segment(self):
        last_seg = c.coords(self.segments[0].instance)
        x = last_seg[0]
        y = last_seg[1]
        self.segments.insert(0, Segment(x, y))


# ─── Запуск ─────────────────────────────────────────
root = Tk()
root.title("PythonicWay Snake")

c = Canvas(root, width=WIDTH, height=HEIGHT, bg="black")
c.pack()
c.focus_set()

segments = [
    Segment(SEG_SIZE, SEG_SIZE),
    Segment(SEG_SIZE * 2, SEG_SIZE),
    Segment(SEG_SIZE * 3, SEG_SIZE)
]

s = Snake(segments)
create_food()

c.bind("<KeyPress>", s.change_direction)

game_loop()
root.mainloop()          # ← mainloop() в самом конце!