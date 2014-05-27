<?hh // strict
namespace Fastuc\Utils;

class Random
{
	/**
	 * @param integer $len
	 * @return string
	 */
	public static function createRandomString( int $len = 8 ) : string
	{
		$alphabet = range( 0, 9 ) + range( 'a', 'z' ) + range( 'A', 'Z' );
		shuffle( $alphabet );
		return implode( '', array_slice( $alphabet, 0, $len ) );
	}
}

