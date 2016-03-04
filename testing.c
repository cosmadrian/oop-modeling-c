#include <stdio.h>
#include <stdlib.h>


/*
	modeling an animal 'class' with several 'subclasses' (dog and cat)
	each 'class' has specific methods as well as inherited methods from the base 'class'
	
	class methods are modeled with function pointers
*/


struct Animal {
	int age;
	int (*getAge)(struct Animal*);
	void (*squeak)();
};

struct Dog {
	struct Animal *base;
	void (*squeak)();
};

struct Cat {
	struct Animal *base;
	void (*squeak)();
	int (*addNumbers)(int,int);
};

int animal_age(struct Animal *a){
	return a->age;
}

void animal_squeak(){
	printf("RAWR!\n");
}
void dog_squeak(){
	printf("WOOF!\n");
}
void cat_squeak(){
	printf("MEOW!\n");
}
int cat_add_nums(int a,int b){
	return a+b;		
}


//constructors
struct Animal *new_Animal(int age){
	printf("Animal created! age: %d\n",age);
	struct Animal *a = (struct Animal*)malloc(sizeof(struct Animal));
	a->age = age;
	a->getAge = animal_age;
	a->squeak = animal_squeak;
	return a;
}

struct Dog *new_Dog(int age){
	printf("New Dog!! ");
	struct Dog *d = (struct Dog*)malloc(sizeof(struct Dog));
	d->base = new_Animal(age);
	d->squeak = dog_squeak;
	return d;
}

struct Cat *new_Cat(int age){
	printf("New Cat!! ");
	struct Cat *c = (struct Cat*)malloc(sizeof(struct Cat));
	c->base = new_Animal(age);
	c->squeak = cat_squeak;
	c->addNumbers = cat_add_nums;
	return c;
}

//destructors
void delete_Animal(struct Animal *a){
	printf("Deleting animal! \n");
	free(a);
}

void delete_Cat(struct Cat *c){
	printf("Deleting cat! \n");
	delete_Animal(c->base);
	free(c);
}

void delete_Dog(struct Dog *d){
	printf("Deleting Dog! \n");
	delete_Animal(d->base);
	free(d);
}


int main(void){
	struct Animal *random_animal = new_Animal(4);
	struct Dog *dog1 = new_Dog(3);
	dog1->squeak();
	dog1->base->squeak();
	
	struct Cat *cat1 = new_Cat(4);
	cat1->squeak();
	printf("This cat's age is %d\n\n",cat1->base->getAge(cat1->base));
	

	delete_Animal(random_animal);
	delete_Cat(cat1);
	delete_Dog(dog1);	
	return 0;	
}


