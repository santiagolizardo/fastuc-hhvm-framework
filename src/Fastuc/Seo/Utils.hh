<?hh // strict
namespace Fastuc\Seo;

class Utils
{
	/**
	 * @param string $text
	 * @param array $stopWords
	 */
	public static function extractKeywords( string $text, array $stopWords = null ) : array
	{
		$step0 = strip_tags( $text );
		$step1 = strtolower( $step0 );
		$step2 = preg_replace( '/[^a-z0-9 ]/', '', $step1 );
		$keywords = explode( ' ', $step2 );

		if( null === $stopWords )
		{
			$stopWords = array();
		}

		$keywords = array_diff( $keywords, $stopWords );

		return $keywords;
	}
}

