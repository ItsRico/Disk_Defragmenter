        #ifndef _QUADRATIC_PROBING_H_
        #define _QUADRATIC_PROBING_H_

        #include <iostream>
        #include "vector.h"
        using namespace std;

        // QuadraticProbing Hash table class
        //
        // CONSTRUCTION: an initialization for ITEM_NOT_FOUND
        //               and an approximate initial size or default of 101
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // void remove( x )       --> Remove x
        // Hashable find( x )     --> Return item that matches x
        // void makeEmpty( )      --> Remove all items
        // int hash( String str, int tableSize )
        //                        --> Static method to hash strings

        template <class HashedObj>
        class QuadraticHashTable
        {
          public:
            explicit QuadraticHashTable( const HashedObj & notFound, int size = 101 );
            QuadraticHashTable( const QuadraticHashTable & rhs )
              : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
                array( rhs.array ), currentSize( rhs.currentSize ) { }
            const HashedObj & find( unsigned ID );
            void makeEmpty( );
            void insert( unsigned ID, const HashedObj & x );
            //void insert( const HashedObj & x );
            void remove( unsigned ID );
            void updateLocation( unsigned ID, const HashedObj & moveto );
            const QuadraticHashTable & operator=( const QuadraticHashTable & rhs );
            void printSize() {cout << "currentSize = " << array.size() << " number of elements " << currentSize << endl;};
            void printTable();
            int getSize();
            enum EntryType { ACTIVE, EMPTY, DELETED };

          private:
            struct HashEntry
            {
                unsigned index;
                HashedObj element;
                EntryType info;

              HashEntry( int hk = 0, const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
                  : index( hk ), element( e ), info( i ) { }
            };

            vector<HashEntry> array;
            int currentSize;
            const HashedObj ITEM_NOT_FOUND;
          
            bool isPrime( int n ) const;
            int nextPrime( int n ) const;
            bool isActive( int currentPos ) const;
            int findPos( unsigned ID ) const;
            int hash( int key, int tableSize ) const;
            void rehash( );
        };

        #include "QuadraticProbing.cpp"
        #endif
