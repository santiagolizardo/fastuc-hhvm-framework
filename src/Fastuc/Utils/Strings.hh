<?hh // strict
namespace Fastuc\Utils;

/**
 * Functions to manipulate strings in different ways.
 */
class Strings
{
	/**
	 * Removes or replaces non-ascii characters from the given string.
	 *
	 * @param string $string
	 * @return string
	 */
	public static function sanitize( string $string ) : string
	{
		if( null === $string ) return null;

		$string = trim( $string );
		$string = strtolower( $string );
		$string = self::transliterate( $string );
		$string = preg_replace( '/[^a-z0-9-_\s]/', '', $string );
		$string = preg_replace( '/\s+/', '-', $string );

		return $string;
	}

	/**
	 * @param string $string
	 * @return string
	 */
	public static function capitalizeWords( string $string ) : string
	{
		return preg_replace_callback(
			'/[a-z][a-zA-Z]*/',
			function( array $matches )
			{
				return ucfirst( $matches[0] );
			},
			$string
		);
	}

	/**
	 * @param string $string
	 * @return string
	 */
	public static function transliterate( string $string ) : string
	{
		return strtr( utf8_decode( $string ),
			utf8_decode( 'ŠŒŽšœžŸ¥µÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýÿ' ),
			'SOZsozYYuAAAAAAACEEEEIIIIDNOOOOOOUUUUYsaaaaaaaceeeeiiiionoooooouuuuyy'
		);
	}

	/**
	 * @param string $string
	 * @return string
	 */
	public static function unsanitize( string $string ) : string
	{
		return str_replace( '-', ' ', $string );
	}

	/**
	 * @param string $underscore
	 * @return string
	 */
	public static function toCamelCase( string $underscore ) : string
	{
		$string = strtolower( $underscore );
		$string = preg_replace_callback(
			'/_([a-z])/',
			function( $matching ) { return strtoupper( $matching[1] ); },
			$string
		);
		return $string;
	}
}

