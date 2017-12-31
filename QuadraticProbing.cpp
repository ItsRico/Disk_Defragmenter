#include "QuadraticProbing.h"
#include <iostream>
using namespace std;


        /**
         * Internal method to test if a positive number is prime.
         * Not an efficient algorithm.
         */
        template <class HashedObj>
        bool QuadraticHashTable<HashedObj>::isPrime( int n ) const
        {
            if( n == 2 || n == 3 )
                return true;

            if( n == 1 || n % 2 == 0 )
                return false;

            for( int i = 3; i * i <= n; i += 2 )
                if( n % i == 0 )
                    return false;

            return true;
        }

        /**
         * Internal method to return a prime number at least as large as n.
         * Assumes n > 0.
         */
        template <class HashedObj>
        int QuadraticHashTable<HashedObj>::nextPrime( int n ) const
        {
            if( n % 2 == 0 )
                n++;

            for( ; !isPrime( n ); n += 2 )
                ;

            return n;
        }

        /**
         * Construct the hash table.
         */
        template <class HashedObj>
        QuadraticHashTable<HashedObj>::QuadraticHashTable( const HashedObj & notFound, int size )
          : array( nextPrime( size ) ), ITEM_NOT_FOUND( notFound )
        {
            makeEmpty( );
        }



template < class HashedObj>
int QuadraticHashTable<HashedObj>::getSize()
{
  return currentSize;
}
/**
 * Insert item x into the hash table. If the item is
 * already present, then do nothing.
 */
template <class HashedObj>
void QuadraticHashTable<HashedObj>::insert( unsigned ID, const HashedObj & x )
{

  int currentPos = findPos( ID );
  if( isActive( currentPos ) ) {
    return;
  }
  array[ currentPos ] = HashEntry( ID, x, ACTIVE );
  
  if( ++currentSize > (double)array.size( ) / 1.1 )
    rehash( );
}



        /**
         * Expand the hash table.
         */
        template <class HashedObj>
        void QuadraticHashTable<HashedObj>::rehash( )
        {
            vector<HashEntry> oldArray = array;

                // Create new double-sized, empty tablenextPrime( 1.0 * oldArray.size( ) ) 
            array.resize( nextPrime( 1.8 * oldArray.size()));
            for( int j = 0; j < array.size( ); j++ )
                array[ j ].info = EMPTY;

            currentSize = 0;
            for( int i = 0; i < oldArray.size( ); i++ )
                if( oldArray[ i ].info == ACTIVE )
                    insert( oldArray[ i ].index, oldArray[ i ].element );
        }



template <class HashedObj>
int QuadraticHashTable<HashedObj>::findPos( unsigned ID ) const
{
  /* 1*/      int collisionNum = 0;
  /* 2*/      int currentPos = hash( ID, array.size( ) );
  
  /* 3*/      while( array[ currentPos ].info != EMPTY &&
                    array[ currentPos ].index != ID )
  {
    
              currentPos += 2 * ++collisionNum - 1;  // Compute ith probe
    /* 5*/          if( currentPos >= array.size( ) )
    /* 6*/              currentPos -= array.size( );
  }
  
  /* 7*/      return currentPos;
}


        /**
         * Remove item x from the hash table.
         */
        template <class HashedObj>
        void QuadraticHashTable<HashedObj>::remove( unsigned ID )
        {
            int currentPos = findPos( ID );
            if( isActive( currentPos ) )
                array[ currentPos ].info = DELETED;
        }

        /**
         * Find item x in the hash table.
         * Return the matching item, or ITEM_NOT_FOUND, if not found.
         */
        template <class HashedObj>
        const HashedObj & QuadraticHashTable<HashedObj>::find( unsigned ID )
        {
            int currentPos = findPos( ID );
            return isActive( currentPos ) ? array[ currentPos ].element : ITEM_NOT_FOUND;
        }

        /**
         * Make the hash table logically empty.
         */
        template <class HashedObj>
        void QuadraticHashTable<HashedObj>::makeEmpty( )
        {
            // cout << "making empty" << endl;
            currentSize = 0;
            for( int i = 0; i < array.size( ); i++ )
                array[ i ].info = EMPTY;
        }

        /**
         * Deep copy.
         */
        template <class HashedObj>
        const QuadraticHashTable<HashedObj> & QuadraticHashTable<HashedObj>::
        operator=( const QuadraticHashTable<HashedObj> & rhs )
        {
            if( this != &rhs )
            {
                array = rhs.array;
                currentSize = rhs.currentSize;
            }
            return *this;
        }


        /**
         * Return true if currentPos exists and is active.
         */
        template <class HashedObj>
        bool QuadraticHashTable<HashedObj>::isActive( int currentPos ) const
        {
            return array[ currentPos ].info == ACTIVE;
        }


        /**
         * A hash routine for ints.
         */
         template <class HashedObj>
        int QuadraticHashTable<HashedObj>::hash( int key, int tableSize ) const
        {
            if( key < 0 ) key = -key;
            return key % tableSize;
        }



template <class HashedObj>
void QuadraticHashTable<HashedObj>::printTable()
{
  for (int i = 0; i < array.size(); i++) {
    if ( isActive(i) ) {
      cout << "key/blockID: " << array[i].index << " value/stored obj: " << array[i].element << endl;
    }
  }
  
}
