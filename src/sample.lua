-- A simple test scene featuring some spherical cows grazing
-- around Stonehenge.  "Assume that cows are spheres..."

stone = gr.material({0.8, 0.7, 0.7}, {0.0, 0.0, 0.0}, 0)
grass = gr.material({0.1, 0.7, 0.1}, {0.0, 0.0, 0.0}, 0)
hide = gr.material({0.84, 0.6, 0.53}, {0.3, 0.3, 0.3}, 20)

red = gr.material({0.8, 0.2, 0.2}, {0.5, 0.7, 0.5}, 25)
blue = gr.material({0.2, 0.2, 0.8}, {0.5, 0.7, 0.5}, 25)
green = gr.material({0.2, 0.8, 0.2}, {0.5, 0.7, 0.5}, 25)
white = gr.material({0.8, 0.8, 0.8}, {0.5, 0.7, 0.5}, 25)
black = gr.material({0.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 10)
yellow = gr.material({0.8, 0.8, 0.0}, {0.5, 0.7, 0.5}, 25)

-- ##############################################
-- the arch
-- ##############################################

inst = gr.node('inst')

arc = gr.node('arc')

arc:rotate('Y', 60)
arc:translate(0, 0, -10)

p1 = gr.nh_box('p1', {0, 0, 0}, 1)
arc:add_child(p1)
p1:set_material(stone)
p1:translate(-2.4, 0, -0.4)
p1:scale(0.8, 4, 0.8)

p2 = gr.nh_box('p2', {0, 0, 0}, 1)
arc:add_child(p2)
p2:set_material(stone)
p2:translate(1.6, 0, -0.4)
p2:scale(0.8, 4, 0.8)

s = gr.nh_sphere('s', {0, 0, 0}, 1)
arc:add_child(s)
s:set_material(stone)
s:translate(0, 4, 0)
s:scale(4, 0.6, 0.6)


-- #############################################
-- A bear
-- #############################################

bear = gr.node('the_bear')

torso = gr.nh_sphere('torso', {0, 0, 0}, 1)
bear:add_child(torso)
torso:set_material(yellow)
torso:scale(2.0, 2.0, 1.5)

shoulder = gr.nh_sphere('shoulder', {0, 0, 0}, 1)
bear:add_child(shoulder)
shoulder:set_material(yellow)
shoulder:translate(0, 2, 0)
shoulder:scale(2.5, 2.0, 2.0)

head = gr.nh_sphere('head', {0, 0, 0}, 1)
bear:add_child(head)
head:set_material(yellow)
head:translate(0, 4.25, 0)
head:scale(3.0, 2.5, 2.5)

nose = gr.nh_sphere('nose', {0, 0, 0}, 1)
bear:add_child(nose)
nose:set_material(white)
nose:translate(0, 4.0, 2.0)

noset = gr.nh_sphere('noset', {0, 0, 0}, 1)
bear:add_child(noset)
noset:set_material(black)
noset:translate(0, 4.5, 3.0)
noset:scale(0.25, 0.25, 0.25)

earl = gr.nh_sphere('earl', {0, 0, 0}, 1)
bear:add_child(earl)
earl:set_material(yellow)
earl:translate(-2.5, 6.25, 0.0)
earl:scale(1.0, 1.0, 0.25)

earr = gr.nh_sphere('earr', {0, 0, 0}, 1)
bear:add_child(earr)
earr:set_material(yellow)
earr:translate(2.5, 6.25, 0.0)
earr:scale(1.0, 1.0, 0.25)

eyel = gr.nh_sphere('eyel', {0, 0, 0}, 1)
bear:add_child(eyel)
eyel:set_material(black)
eyel:translate(-1.0, 4.6, 2.25)
eyel:scale(0.15, 0.5, 0.25)

eyer = gr.nh_sphere('eyer', {0, 0, 0}, 1)
bear:add_child(eyer)
eyer:set_material(black)
eyer:translate(1.0, 4.6, 2.25)
eyer:scale(0.15, 0.5, 0.25)

ual = gr.nh_sphere('ual', {0, 0, 0}, 1)
bear:add_child(ual)
ual:set_material(white)
ual:translate(-2.75, 1.75, 0)
ual:rotate('z', 90)
ual:scale(1.5, 1.75, 1.5)

uar = gr.nh_sphere('uar', {0, 0, 0}, 1)
bear:add_child(uar)
uar:set_material(white)
uar:translate(2.75, 1.75, 0)
uar:scale(1.5, 1.75, 1.5)

el = gr.nh_sphere('el', {0, 0, 0}, 1)
bear:add_child(el)
el:set_material(white)
el:translate(-2.75, 0, 0)
el:scale(0.5, 0.5, 0.5)

er = gr.nh_sphere('er', {0, 0, 0}, 1)
bear:add_child(er)
er:set_material(white)
er:translate(2.75, 0, 0)
er:scale(0.5, 0.5, 0.5)

fal = gr.nh_sphere('fal', {0, 0, 0}, 1)
bear:add_child(fal)
fal:set_material(yellow)
fal:translate(-2.75, -1.75, 0)
fal:scale(1, 1.75, 1)

far = gr.nh_sphere('far', {0, 0, 0}, 1)
bear:add_child(far)
far:set_material(yellow)
far:translate(2.75, -1.75, 0)
far:scale(1, 1.75, 1)

hl = gr.nh_sphere('hl', {0, 0, 0}, 1)
bear:add_child(hl)
hl:set_material(white)
hl:translate(-2.75, -2.70, 0)


hr = gr.nh_sphere('hr', {0, 0, 0}, 1)
bear:add_child(hr)
hr:set_material(white)
hr:translate(2.75, -2.70, 0)

hip = gr.nh_sphere('hip', {0, 0, 0}, 1)
bear:add_child(hip)
hip:set_material(yellow)
hip:translate(0, -1.5, 0)
hip:scale(1.25, 1.25, 1.25)

tl = gr.nh_sphere('tl', {0, 0, 0}, 1)
bear:add_child(tl)
tl:set_material(white)
tl:translate(-1.25, -2.5, 0)
tl:scale(1.5, 1.75, 1.5)

tr = gr.nh_sphere('tr', {0, 0, 0}, 1)
bear:add_child(tr)
tr:set_material(white)
tr:translate(1.25, -2.5, 0)
tr:scale(1.5, 1.75, 1.5)

cl = gr.nh_sphere('cl', {0, 0, 0}, 1)
bear:add_child(cl)
cl:set_material(yellow)
cl:translate(-1.25, -6, 0)
cl:scale(1.75, 2.5, 1.75)

cr = gr.nh_sphere('cr', {0, 0, 0}, 1)
bear:add_child(cr)
cr:set_material(yellow)
cr:translate(1.25, -6, 0)
cr:scale(1.75, 2.5, 1.75)

fl = gr.nh_sphere('fl', {0, 0, 0}, 1)
bear:add_child(fl)
fl:set_material(white)
fl:translate(-1.25, -8.75, 0)
fl:scale(1.5, 1.0, 1.5)

fr = gr.nh_sphere('fr', {0, 0, 0}, 1)
bear:add_child(fr)
fr:set_material(white)
fr:translate(1.25, -8.75, 0)
fr:scale(1.5, 1.0, 1.5)


-- ##############################################
-- the scene
-- ##############################################

scene = gr.node('scene')
scene:rotate('X', 23)

-- the floor

plane = gr.mesh('plane', {
		   { -1, 0, -1 }, 
		   {  1, 0, -1 }, 
		   {  1,  0, 1 }, 
		   { -1, 0, 1  }
		}, {
		   {3, 2, 1, 0}
		})
scene:add_child(plane)
plane:set_material(grass)
plane:scale(30, 30, 30)

-- Construct a central altar in the shape of a buckyball.  The
-- buckyball at the centre of the real Stonehenge was destroyed
-- in the great fire of 733 AD.

require('buckyball')

scene:add_child(buckyball)
buckyball:set_material(stone)
buckyball:scale(1.5, 1.5, 1.5)

-- Use the instanced cow model to place some actual cows in the scene.
-- For convenience, do this in a loop.

bear_number = 1

for _, pt in pairs({
		      {{3,4.8,10}, 20},
		      {{5,4.8,-11}, 180},
		      {{-3.5,2.8,4}, -10}}) do
   bear_instance = gr.node('bear' .. tostring(bear_number))
   scene:add_child(bear_instance)
   bear_instance:add_child(bear)
   bear_instance:translate(unpack(pt[1]))
   bear_instance:rotate('Y', pt[2])
   bear_instance:scale(0.5, 0.5, 0.5)
   
   bear_number = bear_number + 1
end

   bear_instance4 = gr.node('bear4')
   scene:add_child(bear_instance4)
   bear_instance4:add_child(bear)
   bear_instance4:translate(0, 4, 0)
   bear_instance4:rotate('x', -90)
   bear_instance4:rotate('z', 90)
   bear_instance4:scale(0.5, 0.5, 0.5)


-- Place 3 boxes.

boxes = gr.node('boxes')
scene:add_child(boxes)
boxes:translate(-5,0,6)

b1 = gr.nh_box('b1', {0, 0, 0}, 1)
boxes:add_child(b1)
b1:set_material(red)
b1:rotate('y', -20)
b1:scale(2, 2, 2)

b2 = gr.nh_box('2', {0, 0, 0}, 1)
boxes:add_child(b2)
b2:set_material(green)
b2:translate(2,0,0)
b2:rotate('y', 20)
b2:scale(2, 2, 2)

b3 = gr.nh_box('b3', {0, 0, 0}, 1)
boxes:add_child(b3)
b3:set_material(blue)
b3:translate(1,2,0)
b3:scale(2, 2, 2)

-- Place a arc

scene:add_child(arc)

gr.render(scene,
	  'sample.png', 512, 512,
	  {0, 2, 30}, {0, 0, -1}, {0, 1, 0}, 50,
	  {0.4, 0.4, 0.4}, {gr.light({200, 202, 430}, {0.8, 0.8, 0.8}, {1, 0, 0})})
