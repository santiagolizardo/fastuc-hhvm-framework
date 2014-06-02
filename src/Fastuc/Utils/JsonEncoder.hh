<?hh // strict
namespace Fastuc\Utils;

/**
 * This utility class helps to encode to JSON not only primitive types but also array-like objects implementing the \Traversable interface.
 *
 * @see \Traversable
 */
class JsonEncoder
{
	/**
	 * @param \Traversable|string $value
	 */
	public static function encodeToOutputStream( $value ) : string
	{
		$fd = fopen( 'php://output', 'w' );
		self::encode( $value, $fd );
		fclose( $fd );
	}

	/**
	 * @param \Traversable|string $value
	 * @param object $fd
	 */
	public static function encode( mixed $value, mixed $fd ) : void
	{
		if( $value instanceof \Traversable )
		{
			$numValues = count( $value );
			fwrite( $fd, '[' );
			for( $i = 0; $i < $numValues; $i++ )
			{
				fwrite( $fd, json_encode( $value[ $i ] ) );
				if( $i + 1 < $numValues ) fwrite( $fd, ',' );
			}
			fwrite( $fd, ']' );
		}
		else
		{
			fwrite( $fd, json_encode( $value ) );
		}
	}
}

