<?hh // strict
namespace Fastuc\Fs;

class Utils
{
	/**
	 * Converts a file size in bytes into a human (readable) representation.
	 *
	 * @param int $bytes
	 * @return string
	 */
	public static function formatSize( int $bytes, int $precision = 2 ) : string
	{
		$units = [ 'B', 'KB', 'MB', 'GB', 'TB' ];

		$bytes = max( $bytes, 0 );
		$pow = floor( ( $bytes ? log( $bytes ) : 0 ) / log( 1024 ) ); 
		$pow = min( $pow, count( $units ) - 1 ); 

		$bytes /= ( 1 << ( 10 * $pow ) ); 

		return round( $bytes, $precision ) . ' ' . $units[ $pow ]; 
	}
}

